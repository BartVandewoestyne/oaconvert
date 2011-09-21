#include <iostream>
#include <boost/regex.hpp>

#include "airspace.h"
#include "coordinate.h"
#include "parser.h"

using namespace boost;
using namespace std;

Parser::Parser()
: _writer()
{}

Parser::Parser(const std::string& outfile)
: _writer( outfile )
{}

void Parser::setCurrentAirspace(const AirSpace& s)
{
  currentAirSpace = s;
}

AirSpace& Parser::getCurrentAirSpace()
{
  return currentAirSpace;
}

void Parser::setCurrentCoordinate(const Coordinate& c)
{
  currentCoordinate = c;
}

const Coordinate& Parser::getCurrentCoordinate() const
{
  return currentCoordinate;
}

int Parser::getCurrentDirection() const
{
  return currentDirection;
}

Coordinate Parser::getCoordinate(const std::string& s) const
{
  smatch matches;
  regex expression;
  Latitude lat;
  Longitude lon;

  // Example: 101:20:32 S 102:32:12 W
  expression = "[^0-9]*(\\d+):(\\d\\d):(\\d\\d)\\s*([NZSnzs])[\\s,]+(\\d+):(\\d\\d):(\\d\\d)\\s*([OWEowe])*.*";
  if ( regex_match(s, matches, expression) )
  {
    string degreesLat, minutesLat, secondsLat;
    string degreesLon, minutesLon, secondsLon;
    string directionLat, directionLon;

    degreesLat.assign(   matches[1].first, matches[1].second );
    minutesLat.assign(   matches[2].first, matches[2].second );
    secondsLat.assign(   matches[3].first, matches[3].second );
    directionLat.assign( matches[4].first, matches[4].second );
    degreesLon.assign(   matches[5].first, matches[5].second );
    minutesLon.assign(   matches[6].first, matches[6].second );
    secondsLon.assign(   matches[7].first, matches[7].second );
    directionLon.assign( matches[8].first, matches[8].second );

    lat = Latitude(atoi(degreesLat.c_str()),
                   atoi(minutesLat.c_str()),
                   atoi(secondsLat.c_str()), directionLat[0]);
    lon = Longitude(atoi(degreesLon.c_str()),
                    atoi(minutesLon.c_str()),
                    atoi(secondsLon.c_str()), directionLon[0]);
    return Coordinate(lat, lon);
  }

  // Example: 101:20.32 N 102:32.12 E
  expression = "[^0-9]*(\\d+):(\\d+.\\d+)\\s*([NZSnzs])[\\s,]+(\\d+):(\\d+.\\d+)\\s*([OWEowe])*.*";
  if ( regex_match(s, matches, expression) )
  {
    string degreesLat, minutesLat;
    string degreesLon, minutesLon;
    string directionLat, directionLon;

    degreesLat.assign(   matches[1].first, matches[1].second );
    minutesLat.assign(   matches[2].first, matches[2].second );
    directionLat.assign( matches[3].first, matches[3].second );
    degreesLon.assign(   matches[4].first, matches[4].second );
    minutesLon.assign(   matches[5].first, matches[5].second );
    directionLon.assign( matches[6].first, matches[6].second );

    Latitude lat(atoi(degreesLat.c_str()),
                 atof(minutesLat.c_str()),
                 directionLat[0]);
    Longitude lon(atoi(degreesLon.c_str()),
                  atof(minutesLon.c_str()),
                  directionLon[0]);
    return Coordinate(lat, lon);
  }

  cout << "\nERROR: invalid coordinate string: " << s << endl;
  exit(1);
}


void Parser::handleLine(const std::string& line)
{
  smatch matches;
  regex expression;

  expression = "\\s*\\*.*";
  if ( regex_match(line, matches, expression) )
  {
    // do nothing.
  }

  // Although not specified in the OpenAir specs at
  //    http://www.winpilot.com/usersguide/userairspace.asp
  // we *do* accept ICAO airspace classes E, F and G as valid input.
  expression = "\\s*AC\\s+([RQPABCDEFGW]|GP|CTR)\\s*";
  if ( regex_match(line, matches, expression) )
  {
    _writer.write(getCurrentAirSpace());
    getCurrentAirSpace().clear();

    string airspace_class;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      airspace_class.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirSpace().setClass(airspace_class);
  }

  expression = "\\s*AN\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string airspace_name;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      airspace_name.assign(matches[i].first, matches[i].second);
    }
    //cout << "DEBUG: " << airspace_name << endl;
    getCurrentAirSpace().setName(airspace_name);
  }

  expression = "\\s*AH\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string airspace_ceiling;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      airspace_ceiling.assign(matches[i].first, matches[i].second);
    }
    //cout << "DEBUG: " << airspace_ceiling << endl;
    getCurrentAirSpace().setCeiling(airspace_ceiling);
  }

  expression = "\\s*AL\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string airspace_floor;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      airspace_floor.assign(matches[i].first, matches[i].second);
    }
    //cout << "DEBUG: " << airspace_floor << endl;
    getCurrentAirSpace().setFloor(airspace_floor);
  }

  expression = "\\s*AT\\s+(.*)"; // This one is optional.
  if ( regex_match(line, matches, expression) )
  {
    string airspace_coordinate;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      airspace_coordinate.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirSpace().addLabelCoordinate(getCoordinate(airspace_coordinate));
  }

  expression = "\\s*V\\s+X\\s*=\\s*(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string coordinate;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      coordinate.assign(matches[i].first, matches[i].second);
    }
    setCurrentCoordinate(getCoordinate(coordinate));
  }

  expression = "\\s*DP\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string point_coordinate;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      point_coordinate.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirSpace().getPolygon().add(getCoordinate(point_coordinate));
    //cout << "DEBUG: " << getCurrentAirSpace() << endl;
  }

  expression = "\\s*DA\\s+(\\d+\\.*\\d*)[\\s,]+(\\d+)[\\s,]+(\\d+)";
  if ( regex_match(line, matches, expression) )
  {
    // Set coordinate and direction that we have just parsed.
    getCurrentAirSpace().getArc().setCenter(getCurrentCoordinate());
    getCurrentAirSpace().getArc().setDirection(getCurrentDirection());

    // Read the matched values and create our Arc.
    string radiusNM;
    string angleStart;
    string angleEnd;
    radiusNM.assign(   matches[1].first, matches[1].second );
    angleStart.assign( matches[2].first, matches[2].second );
    angleEnd.assign(   matches[3].first, matches[3].second );
    getCurrentAirSpace().getArc().setRadiusNM(atof(radiusNM.c_str()));
    getCurrentAirSpace().getArc().setStartAngle(atof(angleStart.c_str()));
    getCurrentAirSpace().getArc().setEndAngle(atof(angleEnd.c_str()));

    // Add the arc points to this space's Polygon.
    // TODO: don't use *hardcoded* 100 points for the discretization!
    getCurrentAirSpace().getPolygon().add(getCurrentAirSpace().getArc().toPolygon(100));

  }

  expression = "\\s*DC\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {

    //cout << "DEBUG: found DC record!" << endl;
    // Set circle center from stored state of the parser.
    getCurrentAirSpace().getCircle().setCenter(getCurrentCoordinate());

    // Set circle radius (in Nautical Miles) from what we've just read.
    string radiusNM;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      radiusNM.assign(matches[i].first, matches[i].second);
    }

    getCurrentAirSpace().getCircle().setRadiusNM(atof(radiusNM.c_str()));
  }

}

void Parser::finalize()
  {
  _writer.write(currentAirSpace);
  }

void Parser::init()
  {
  _writer.writeHeader();
  }


