/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.

  This file is part of oaconvert.

  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Parser.h"

#include <iostream>
#include <memory>

#include "Airspace.h"
#include "Arc.h"
#include "Constants.h"
#include "Coordinate.h"
#include "Circle.h"
#include "CurvedPolygon.h"
#include "GPXState.h"
#include "KMLState.h"

using namespace std;
using namespace Constants;

Parser::Parser()
    : outputWriter()
    , airspaces()
    , currentDirection('+')
    , currentArcCenter()
    , regexMap()
    , currentLineNumber(0)
{
    initRegexMap();
}

Parser::Parser(const std::string& outfile)
    : outputWriter( outfile )
    , airspaces()
    , currentDirection('+')
    , currentArcCenter()
    , regexMap()
    , currentLineNumber(0)
{

    initRegexMap();

    // Change the state if we have a .gpx extension.
    std::string ext = parseFileExtension(outfile);
    if ( ext == "gpx" )
    {
        outputWriter.changeState(GPXState::getInstance());
    }
    else if ( ext == "kml" )
    {
        outputWriter.changeState(KMLState::getInstance());
    }

}

Parser::~Parser()
{
    for( std::list<Airspace*>::iterator it = airspaces.begin(); it != airspaces.end(); ++it )
    {
        delete *it;
    }
    airspaces.clear();
}

const std::shared_ptr<Coordinate> Parser::getCurrentArcCenter() const
{
    return currentArcCenter;
}

char Parser::getCurrentDirection() const
{
    return currentDirection;
}

void Parser::setCurrentArcCenter(const Coordinate& c)
{
    currentArcCenter = std::make_shared<Coordinate>(c);
}

void Parser::setCurrentDirection(char d)
{
    currentDirection = d;
}

/**
  * Parse a string that should contain a coordinate in lat/lon
  * format and return it as a Coordinate object.  If the string
  * is not a valid coordinate, exit with an error message.
  */
Coordinate Parser::parseCoordinate(const std::string& s) const
{
    smatch matches;

    // Example: 101:20:32 S 102:32:12 W
    if ( regex_match(s, matches, regexMap.find(REGEX_DDMMSS)->second) )
    {
        string degreesLat(   matches[1].first, matches[1].second );
        string minutesLat(   matches[2].first, matches[2].second );
        string secondsLat(   matches[3].first, matches[3].second );
        string directionLat( matches[4].first, matches[4].second );
        string degreesLon(   matches[5].first, matches[5].second );
        string minutesLon(   matches[6].first, matches[6].second );
        string secondsLon(   matches[7].first, matches[7].second );
        string directionLon( matches[8].first, matches[8].second );

        Latitude lat = Latitude(atoi(degreesLat.c_str()),
                                atoi(minutesLat.c_str()),
                                atof(secondsLat.c_str()), directionLat[0]);
        Longitude lon = Longitude(atoi(degreesLon.c_str()),
                                  atoi(minutesLon.c_str()),
                                  atof(secondsLon.c_str()), directionLon[0]);
        return Coordinate(lat, lon);
    }

    // Example: 101:20.32 N 102:32.12 E
    if ( regex_match(s, matches, regexMap.find(REGEX_DDMM)->second) )
    {
        string degreesLat(   matches[1].first, matches[1].second );
        string minutesLat(   matches[2].first, matches[2].second );
        string directionLat( matches[3].first, matches[3].second );
        string degreesLon(   matches[4].first, matches[4].second );
        string minutesLon(   matches[5].first, matches[5].second );
        string directionLon( matches[6].first, matches[6].second );

        Latitude lat(atoi(degreesLat.c_str()),
                     atof(minutesLat.c_str()),
                     directionLat[0]);
        Longitude lon(atoi(degreesLon.c_str()),
                      atof(minutesLon.c_str()),
                      directionLon[0]);
        return Coordinate(lat, lon);
    }

    // Example: 45.32 N 102.12 E
    if ( regex_match(s, matches, regexMap.find(REGEX_DD)->second) )
    {
        string degreesLat(   matches[1].first, matches[1].second );
        string directionLat( matches[2].first, matches[2].second );
        string degreesLon(   matches[3].first, matches[3].second );
        string directionLon( matches[4].first, matches[4].second );

        Latitude  lat( atof(degreesLat.c_str()), directionLat[0] );
        Longitude lon( atof(degreesLon.c_str()), directionLon[0] );
        return Coordinate(lat, lon);
    }

    cout << "\nERROR: invalid coordinate string: " << s << endl;
    exit(1);
}

/**
  * Parse the given altitude specification and return the value in meter.
  *
  * TODO: I'm not sure how all of these must be translated for the KML output...
  */
double Parser::parseAltitude(const std::string& s) const
{

    smatch matches;

    // Flight Level altitudes are 'pressure altitudes' with reference
    // pressure 1013.25 hPa!!!
    // For example, FL 90 means 9000 ft above the 1013.25 hPa reference altitude.
    //
    // See also:
    //   http://en.wikipedia.org/wiki/Flight_level
    //
    // Examples:
    //   FL 55
    //   FL55
    //   FL 55 foobar
    if ( regex_match(s, matches, regexMap.find(REGEX_FL)->second) )
    {
        string valuestring( matches[1].first, matches[1].second );
        return atof(valuestring.c_str())*100*feet_in_meter;
    }

    // AGL means 'Above Ground Level', which means that this altitude is measured
    // with respect to the underlying ground surface.
    //
    // See also:
    //   http://en.wikipedia.org/wiki/Above_ground_level
    //
    // Examples:
    //   820 AGL
    //   7000 ft AGL
    if ( regex_match(s, matches, regexMap.find(REGEX_AGL)->second) )
    {
        string valuestring( matches[1].first, matches[1].second );
        return atof(valuestring.c_str())*feet_in_meter;
    }

    // AAL means 'Above Aerodrome Level', which means that this altitude is measured
    // with respect to a reference point on the aerodrome.
    //
    // See also:
    //   http://nl.wikipedia.org/wiki/Above_Aerodrome_Level
    //
    // Examples:
    //   820 AAL
    //   7000 ft AAL
    if ( regex_match(s, matches, regexMap.find(REGEX_AGL)->second) )
    {
        string valuestring( matches[1].first, matches[1].second );
        return atof(valuestring.c_str())*feet_in_meter;
    }

    // AMSL means 'Above Mean Sea Level' and refers to the altitude relative to the average sea level datum.
    //
    // See also:
    //  http://en.wikipedia.org/wiki/Above_mean_sea_level
    //
    // Examples:
    //   7000 ft MSL
    //   7000 ft AMSL
    //   7000' AMSL
    if ( regex_match(s, matches, regexMap.find(REGEX_AMSL)->second) )
    {
        string valuestring( matches[1].first, matches[1].second );
        return atof(valuestring.c_str())*feet_in_meter;
    }

    // MSL means 'Mean Sea Level'.
    //
    // Examples:
    //   7000 ft MSL
    //   MSL
    if ( regex_match(s, matches, regexMap.find(REGEX_MSL)->second) )
    {
        string valuestring( matches[1].first, matches[1].second );
        return atof(valuestring.c_str())*feet_in_meter; // TODO: check if this is correct!
    }

    // Examples:
    //   820 SFC
    //   SFC
    if ( regex_match(s, matches, regexMap.find(REGEX_SFC)->second) )
    {
        string valuestring( matches[1].first, matches[1].second );
        return atof(valuestring.c_str())*feet_in_meter; // TODO: check if this is correct!
    }

    // Examples:
    //   820
    //   7000 ft
    // Note: we consider these as AMSL altitudes!!!
    if ( regex_match(s, matches, regexMap.find(REGEX_FT)->second) )
    {
        string valuestring( matches[1].first, matches[1].second );
        return atof(valuestring.c_str())*feet_in_meter; // TODO: check if this is correct!
    }

    // Examples:
    //   GND
    if ( regex_match(s, matches, regexMap.find(REGEX_GND)->second) )
    {
        return 0.0; // TODO: check this!  Is GND always = 0 meter ???  Probably not...
    }

    // Examples:
    //   (Airspace Floor)
    if ( regex_match(s, matches, regexMap.find(REGEX_AIRSPACE_FLOOR)->second) )
    {
        return -1.0; // TODO: what is this???
    }

    // Example: UNL or UNLD or UNLIM or UNLIM or UNLIMITED
    if ( regex_match(s, matches, regexMap.find(REGEX_UNLIMITED)->second) )
    {
        // We model UNLIMITED heights as FL 95 for now... since this is the
        // maximum altitude appearing on our airspace maps.
        return 95*100*feet_in_meter;
    }

    // Example: Ask on 122.8
    if ( regex_match(s, matches, regexMap.find(REGEX_ASK)->second) )
    {
        return -1.0; // TODO: handle 'Ask on...'
    }

    if ( regex_match(s, matches, regexMap.find(REGEX_NOTAM)->second) )
    {
        return -1.0; // TODO: handle 'NOTAM ...'
    }

    if ( regex_match(s, matches, regexMap.find(REGEX_CTA)->second) )
    {
        return -1.0; // TODO: handle 'CTA ...'
    }



    cerr << "ERROR: incorrect altitude specification: " << s << endl;
    exit(EXIT_FAILURE);

}

std::string Parser::parseAirspaceClass(const std::string& clss) const
{
    smatch matches;

    if ( regex_match(clss, matches, regexMap.find(REGEX_AIRSPACE_CLASS)->second) )
    {
        string airspace_class( matches[1].first, matches[1].second );
        return airspace_class;
    }

    cerr << "ERROR: invalid airspace class: " << clss << endl;
    exit(EXIT_FAILURE);
}

std::string Parser::parseFileExtension(const std::string& fileName) const
{
    if (fileName.find_last_of(".") != std::string::npos)
    {
        return fileName.substr(fileName.find_last_of(".")+1);
    }
    return "";
}

void Parser::handleLine(const std::string& line)
{
    currentLineNumber++;

    smatch matches;

    if ( regex_match(line, matches, regexMap.find(REGEX_COMMENT)->second) )
    {
        // do nothing.
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_AC)->second) )
    {
        airspaces.push_back(new Airspace);

        setCurrentDirection('+');
        currentArcCenter.reset();

        // Assign the parsed class to the current airspace.
        string matched_text( matches[1].first, matches[1].second );
        getCurrentAirspace()->setClass( parseAirspaceClass(matched_text) );
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_AN)->second) )
    {
        string airspace_name( matches[1].first, matches[1].second );
        Airspace* currentAirspace = getCurrentAirspace();
        if (currentAirspace)
        {
            currentAirspace->setName(airspace_name);
        }
        else
        {
            cout << "\nERROR (line " << currentLineNumber << ") : assign a class to the airspace before giving it a name." << line << endl;
            exit(1);
        }
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_AH)->second) )
    {
        string airspace_ceiling(matches[1].first, matches[1].second);
        getCurrentAirspace()->setCeilingString(airspace_ceiling);
        getCurrentAirspace()->setCeiling( parseAltitude(airspace_ceiling) );
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_AL)->second) )
    {
        string airspace_floor(matches[1].first, matches[1].second);
        getCurrentAirspace()->setFloorString(airspace_floor);
        getCurrentAirspace()->setFloor( parseAltitude(airspace_floor) );
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_AT)->second) )
    {
        string airspace_coordinate(matches[1].first, matches[1].second);
        getCurrentAirspace()->add( Label(getCurrentAirspace()->getName(), parseCoordinate(airspace_coordinate)) );
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_VX)->second) )
    {
        string matched_text(matches[1].first, matches[1].second);

        Airspace* currentAirspace = getCurrentAirspace();
        if (currentAirspace)
        {
            setCurrentArcCenter(parseCoordinate(matched_text));
        }
        else
        {
            unknownAirspaceError(currentLineNumber, line);
            exit(1);
        }
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_VD)->second) )
    {
        string direction_string;
        for (unsigned int i = 1; i < matches.size(); ++i)
        {
            direction_string.assign(matches[i].first, matches[i].second);
        }
        
        Airspace* currentAirspace = getCurrentAirspace();
        if (currentAirspace)
        {
            setCurrentDirection(direction_string[0]);
        }
        else
        {
            unknownAirspaceError(currentLineNumber, line);
            exit(1);
        }
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_DP)->second) )
    {
        string point_coordinate( matches[1].first, matches[1].second );
        
        Airspace* currentAirspace = getCurrentAirspace();
        if (currentAirspace)
        {
            currentAirspace->add( new Point(parseCoordinate(point_coordinate)) );
        }
        else
        {
            unknownAirspaceError(currentLineNumber, line);
            exit(1);
        }
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_DA)->second) )
    {
        // Read the matched values and create our Arc.
        string radiusNM(   matches[1].first, matches[1].second );
        string angleStart( matches[2].first, matches[2].second );
        string angleEnd(   matches[3].first, matches[3].second );

        Arc arc( *(getCurrentArcCenter()), atof(radiusNM.c_str()),
                 atof(angleStart.c_str()), atof(angleEnd.c_str()), getCurrentDirection());

        Airspace* currentAirspace = getCurrentAirspace();
        if (currentAirspace)
        {
            currentAirspace->add( &arc );
        }
        else
        {
            unknownAirspaceError(currentLineNumber, line);
            exit(1);
        }
        return;
    }

    if ( regex_match(line, matches, regexMap.find(REGEX_DB)->second) )
    {
        // We have a DB-record, now check if the coords are specified correctly...
        string dbcoords( matches[1].first, matches[1].second );
        if ( regex_match(dbcoords, matches, regexMap.find(REGEX_DB_COORDS)->second) )
        {
            // Fetch the start and end coordinate for this arc.
            string coord1( matches[1].first, matches[1].second );
            string coord2( matches[2].first, matches[2].second );
            Coordinate c1 = parseCoordinate(coord1);
            Coordinate c2 = parseCoordinate(coord2);

            std::shared_ptr<Coordinate> currentArcCenter = getCurrentArcCenter();

            // Retrieve latitude and longitude of the arc-center.
            Latitude lat = currentArcCenter->getLatitude();
            Longitude lon = currentArcCenter->getLongitude();

            // Compute arcdegree of latitude respectively longitude, based on the center's coordinates.
            double arcdegree_lat = lat.getArcDegree();
            double arcdegree_lon = lon.getArcDegree(lat);

            // Compute start and end angle (in standard coordinate frame!)
            // Note that we have to take into account the arcdegrees here!!!
            double dLat1 = ( c1.getLatitude().getAngle()  - currentArcCenter->getLatitude().getAngle()  )*arcdegree_lat;
            double dLon1 = ( c1.getLongitude().getAngle() - currentArcCenter->getLongitude().getAngle() )*arcdegree_lon;
            double dLat2 = ( c2.getLatitude().getAngle()  - currentArcCenter->getLatitude().getAngle()  )*arcdegree_lat;
            double dLon2 = ( c2.getLongitude().getAngle() - currentArcCenter->getLongitude().getAngle() )*arcdegree_lon;
            double startAngle = 180.0*atan2(dLat1, dLon1)/pi;
            double endAngle   = 180.0*atan2(dLat2, dLon2)/pi;

            // Convert start and end angle to airspace coordinate frame.
            startAngle = 90 - startAngle;
            endAngle   = 90 - endAngle;

            // Use maximum of the two radii (for safety reasons).
            //double radius = max( c1.getDistance(getCurrentCoordinate()), c2.getDistance(getCurrentCoordinate()) );
            // Use minimum of the two radii.
            //double radius = min( c1.getDistance(getCurrentCoordinate()), c2.getDistance(getCurrentCoordinate()) );
            // Use average of the two radii.
            double radius = ( c1.getDistance(*currentArcCenter) + c2.getDistance(*currentArcCenter) )*0.5;

            Airspace* currentAirspace = getCurrentAirspace();
            if (currentAirspace)
            {
                // Add the arc points to this space's Polygon.
                currentAirspace->add( new Arc(*currentArcCenter,
                                                radius/1852.0, startAngle, endAngle, getCurrentDirection()) );
            }
            else
            {
                unknownAirspaceError(currentLineNumber, line);
                exit(1);
            }
        }
        else
        {
            cout << "\nERROR at line " << currentLineNumber << ": invalid coordinate string specification in DB-record: " << line << endl;
            exit(1);
        }

    }

    if ( regex_match(line, matches, regexMap.find(REGEX_DC)->second) )
    {
        // Get circle radius (in Nautical Miles) from what we've just read.
        string radiusNM;
        radiusNM.assign(matches[1].first, matches[1].second);

        // Add circle to this Airspace.
        Point center(*(getCurrentArcCenter()));

        Airspace* currentAirspace = getCurrentAirspace();
        if (currentAirspace)
        {
            currentAirspace->add(new Circle(center, atof(radiusNM.c_str())));
        }
        else
        {
            unknownAirspaceError(currentLineNumber, line);
            exit(1);
        }

    }
}


/**
  * Write out all currently parsed airspaces.
  */
void Parser::writeAirspaces()
{
    airspaces.sort(Airspace_ptr_cmp());

    outputWriter.writeHeader();

    for ( std::list<Airspace*>::iterator it = airspaces.begin();
          it != airspaces.end();
          ++it )
    {
        // TODO: we could check if the airspace is valid before writing
        // it out.  E.g. it must have a valid airspace class and a lower
        // and upper limit.
        outputWriter.write(**it);
    }

    outputWriter.writeFooter();
}


// You can test these at for example
//   http://www.internetofficer.com/seo-tool/regex-tester/
// Do not forget to change each '\\' to '\'
void Parser::initRegexMap()
{
    // Coordinate specification stuff.
    regexMap[REGEX_DDMMSS] = regex("\\s*(\\d{1,3}):(\\d{1,2}):(\\d{1,2}(?:.\\d+)?)\\s*([NS])[\\s,]+(\\d{1,3}):(\\d{1,2}):(\\d{1,2}(?:.\\d+)?)\\s*([WE]).*",
                                   std::regex_constants::icase);
    regexMap[REGEX_DDMM]   = regex("\\s*(\\d{1,3}):(\\d{1,2}.\\d+)\\s*([NS])[\\s,]+(\\d{1,3}):(\\d{1,2}.\\d+)\\s*([WE]).*",
                                   std::regex_constants::icase);
    regexMap[REGEX_DD]     = regex("\\s*(\\d{1,3}.\\d+)\\s*([NS])[\\s,]+(\\d{1,3}.\\d+)\\s*([WE]).*",
                                   std::regex_constants::icase);

    // Altitude specification stuff.
    regexMap[REGEX_FT]             = regex("\\s*(\\d+)\\s*('|ft)?.*",         std::regex_constants::icase);
    regexMap[REGEX_FL]             = regex("\\s*FL\\s*(\\d+).*",              std::regex_constants::icase);
    regexMap[REGEX_AGL]            = regex("\\s*(\\d+)\\s*('|ft)?\\s*AGL.*",  std::regex_constants::icase);
    regexMap[REGEX_AAL]            = regex("\\s*(\\d+)\\s*('|ft)?\\s*AAL.*",  std::regex_constants::icase);
    regexMap[REGEX_AMSL]           = regex("\\s*(\\d+)\\s*('|ft)?\\s*AMSL.*", std::regex_constants::icase);
    regexMap[REGEX_MSL]            = regex("\\s*(\\d*)\\s*('|ft)?\\s*MSL.*",  std::regex_constants::icase);
    // TODO: REGEX_SFC incorrectly matches 'ft ASFC'.  If there is 'ft', then there should be a number in front of it!  But simply 'SFC' should also be allowed... probably the same problem for REGEX_MSL...
    regexMap[REGEX_SFC]            = regex("\\s*(\\d*)\\s*('|ft)?\\s*A?SFC.*", std::regex_constants::icase);
    regexMap[REGEX_GND]            = regex("\\s*GND.*",                        std::regex_constants::icase);
    regexMap[REGEX_AIRSPACE_FLOOR] = regex("\\s*Airspace\\s*Floor.*",          std::regex_constants::icase);
    regexMap[REGEX_UNLIMITED]      = regex("\\s*UNL.*",                        std::regex_constants::icase);
    regexMap[REGEX_ASK]            = regex("\\s*Ask.*",                        std::regex_constants::icase);
    regexMap[REGEX_NOTAM]          = regex("\\s*NOTAM.*",                      std::regex_constants::icase);
    regexMap[REGEX_CTA]            = regex("\\s*CTA.*",                      std::regex_constants::icase);

    regexMap[REGEX_COMMENT]        = "\\s*\\*.*";

    // Valid airspace classes.  Although not specified in the OpenAir specs at
    //
    //    http://www.winpilot.com/usersguide/userairspace.asp
    //
    // we *do* accept some other ICAO airspace classes as valid input.  We also
    // allow the specification of multiple airspace classes, separated by
    // forward slashes and without spaces in between.
    //
    // Note: 'TMZ' stands for 'Transponder Mandatory Zone' and is an
    //       abbreviation found in the Dutch AIP (Part 2 EN ROUTE, ENR 2.2, 4)
    //       but is not contained in ICAO Doc 8400.
    //
    // TODO: use back reference in this regular expression.
    regexMap[REGEX_AIRSPACE_CLASS] =
        regex("\\s*((CTR|TMZ|GP|[ABCDEFGPQRW])(/(CTR|TMZ|GP|[ABCDEFGPQRW])+)*)\\s*");

    // Valid DB arc coordinate specifications.
    // TODO: check if we can make this regex shorter...
    regexMap[REGEX_DB_COORDS] = "\\s*(.*[NS]\\s*,?.*[EW]\\s*)\\s*,\\s*(.*[NS]\\s*,?.*[EW]\\s*)\\s*";

    // Airspace record stuff.
    regexMap[REGEX_AC] = "\\s*AC\\s+(.*)(\\*.*)?";
    regexMap[REGEX_AN] = "\\s*AN\\s+(.*)(\\*.*)?";
    regexMap[REGEX_AH] = "\\s*AH\\s+(.*)(\\*.*)?";
    regexMap[REGEX_AL] = "\\s*AL\\s+(.*)(\\*.*)?";
    regexMap[REGEX_AT] = "\\s*AT\\s+(.*)(\\*.*)?";
    regexMap[REGEX_VX] = "\\s*V\\s+X\\s*=\\s*(.*)(?:\\*.*)?";
    regexMap[REGEX_VD] = "\\s*V\\s+D\\s*=\\s*(.*)(?:\\*.*)?";
    regexMap[REGEX_DP] = "\\s*DP\\s+(.*)(\\*.*)?";
    regexMap[REGEX_DA] = "\\s*DA\\s+(\\d+\\.*\\d*)[\\s,]+(\\d+)[\\s,]+(\\d+)(\\*.*)?";
    regexMap[REGEX_DB] = "\\s*DB\\s+(.*)(\\*.*)?";
    regexMap[REGEX_DC] = "\\s*DC\\s+(.*)(\\*.*)?";
}

void Parser::unknownAirspaceError(unsigned int lineNumber, const std::string& lineText)
{
    cout << "\nERROR at line " << lineNumber << ": unknown airspace." << endl << endl;
    cout << "  " << lineText << endl << endl;
    cout << "=> First create an airspace with AC, AN, AL and AH records before assigning it a geometry." << endl;
}