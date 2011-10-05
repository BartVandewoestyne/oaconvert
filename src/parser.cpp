#include "parser.h"

#include <iostream>
#include <boost/regex.hpp>

#include "Airspace.h"
#include "Arc.h"
#include "constants.h"
#include "Coordinate.h"
#include "Circle.h"
#include "CurvedPolygon.h"

using namespace boost;
using namespace std;
using namespace Constants;

Parser::Parser()
: _writer()
, airspaces(1, new Airspace) // at least 1 airspace
, curved_polygon(0)
{
//  std::cout << "Parser::Parser()" << std::endl;
}

Parser::Parser(const std::string& outfile)
: _writer( outfile )
, airspaces(1, new Airspace) // at least 1 airspace
, curved_polygon(0)
{
//  std::cout << "Parser::Parser(outfile)" << std::endl;
}

Parser::~Parser()
{
  for( std::list<Airspace*>::iterator it = airspaces.begin(); it != airspaces.end(); ++it )
  {
    delete *it;
  }
  airspaces.clear();
}

const Coordinate& Parser::getCurrentCoordinate() const
{
  return currentCoordinate;
}

char Parser::getCurrentDirection() const
{
  return currentDirection;
}

void Parser::setCurrentCoordinate(const Coordinate& c)
{
  currentCoordinate = c;
}

void Parser::setCurrentDirection(char d)
{
  currentDirection = d;
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
  cout << "Read line: '" << line << "'" << endl;

  smatch matches;
  regex expression;

  expression = "\\s*\\*.*";
  if ( regex_match(line, matches, expression) )
  {
    // do nothing.
    return;
  }

  // Although not specified in the OpenAir specs at
  //    http://www.winpilot.com/usersguide/userairspace.asp
  // we *do* accept ICAO airspace classes E, F and G as valid input.
  expression = "\\s*AC\\s+([RQPABCDEFGW]|GP|CTR)\\s*";
  if ( regex_match(line, matches, expression) )
  {
    // Write the current airspace but do not delete it just yet...
    Airspace* airspace = getCurrentAirspace();
    if (airspace)
    {
      _writer.write(*airspace);
    }

    // Create a new airspace and reset the helper curved_polygon and direction.
    airspaces.push_back(new Airspace);
    curved_polygon = 0;
    setCurrentDirection('+');

    string airspace_class;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      airspace_class.assign(matches[i].first, matches[i].second);
    }
    //cout << "DEBUG: " << airspace_class << endl;
    getCurrentAirspace()->setClass(airspace_class);
    return;
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
    getCurrentAirspace()->setName(airspace_name);
    return;
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
    getCurrentAirspace()->setCeiling(airspace_ceiling);
    return;
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
    getCurrentAirspace()->setFloor(airspace_floor);
    return;
  }

  expression = "\\s*AT\\s+(.*)"; // This one is optional.
  // TODO: fix this!! We need the string and the coordinates!
  if ( regex_match(line, matches, expression) )
  {
    string airspace_coordinate;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      airspace_coordinate.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirspace()->addLabelCoordinate("TODO_DUMMY", getCoordinate(airspace_coordinate));
    return;
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
    return;
  }

  expression = "\\s*V\\s+D\\s*=\\s*(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string direction_string;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      direction_string.assign(matches[i].first, matches[i].second);
    }
    setCurrentDirection(direction_string[0]);
    return;
  }

  expression = "\\s*DP\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string point_coordinate;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      point_coordinate.assign(matches[i].first, matches[i].second);
    }
    if( ! curved_polygon )
    {
      curved_polygon = getCurrentAirspace()->addCurvedPolygon();
    }
    curved_polygon->addLinearSegment(getCoordinate(point_coordinate));
    //cout << "DEBUG: " << getCurrentAirspace() << endl;
    return;
  }

  expression = "\\s*DA\\s+(\\d+\\.*\\d*)[\\s,]+(\\d+)[\\s,]+(\\d+)";
  if ( regex_match(line, matches, expression) )
  {
    // Read the matched values and create our Arc.
    string radiusNM;
    radiusNM.assign(   matches[1].first, matches[1].second );

    string angleStart;
    angleStart.assign( matches[2].first, matches[2].second );

    string angleEnd;
    angleEnd.assign(   matches[3].first, matches[3].second );

    Arc arc( getCurrentCoordinate(), atof(radiusNM.c_str()), 
             atof(angleStart.c_str()), atof(angleEnd.c_str()), getCurrentDirection());

    // Add the arc points to this space's Polygon.
    // TODO: don't use *hardcoded* 100 points for the discretization!
    if( ! curved_polygon )
    {
      curved_polygon = getCurrentAirspace()->addCurvedPolygon();
    }
    curved_polygon->addArc(arc);
    return;
  }

  // TODO: check this matching pattern
  expression = "\\s*DB\\s+(.*)\\s*,\\s*(.*)";
  if ( regex_match(line, matches, expression) )
  {
    // Fetch the start and end coordinate for this arc.
    string coord1, coord2;
    coord1.assign(matches[1].first, matches[1].second);
    coord2.assign(matches[2].first, matches[2].second);
    Coordinate c1 = getCoordinate(coord1);
    Coordinate c2 = getCoordinate(coord2);

    // Retrieve latitude and longitude of the arc-center.
    Latitude lat = getCurrentCoordinate().getLatitude();
    Longitude lon = getCurrentCoordinate().getLongitude();

    // Compute arcdegree of latitude respectively longitude, based on the center's coordinates.
    double arcdegree_lat = lat.getArcDegree();
    double arcdegree_lon = lon.getArcDegree(lat);

    // Compute start and end angle (in standard coordinate frame!)
    // Note that we have to take into account the arcdegrees here!!!
    double dLat1 = ( c1.getLatitude().getAngle()  - getCurrentCoordinate().getLatitude().getAngle()  )*arcdegree_lat;
    double dLon1 = ( c1.getLongitude().getAngle() - getCurrentCoordinate().getLongitude().getAngle() )*arcdegree_lon;
    double dLat2 = ( c2.getLatitude().getAngle()  - getCurrentCoordinate().getLatitude().getAngle()  )*arcdegree_lat;
    double dLon2 = ( c2.getLongitude().getAngle() - getCurrentCoordinate().getLongitude().getAngle() )*arcdegree_lon;
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
    double radius = ( c1.getDistance(getCurrentCoordinate()) + c2.getDistance(getCurrentCoordinate()) )*0.5;

    // Create the arc
    Arc arc( getCurrentCoordinate(), radius/1852.0, startAngle, endAngle, getCurrentDirection());

    // Add the arc points to this space's Polygon.
    // TODO: don't use *hardcoded* 100 points for the discretization!
    curved_polygon->addArc( arc );

  }

  expression = "\\s*DC\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    //cout << "DEBUG: found DC record!" << endl;
    // Get circle radius (in Nautical Miles) from what we've just read.
    string radiusNM;
    for (unsigned int i = 1; i < matches.size(); ++i)
    {
      radiusNM.assign(matches[i].first, matches[i].second);
    }

    if( ! curved_polygon )
    {
      getCurrentAirspace()->addCircle(getCurrentCoordinate(), atof(radiusNM.c_str()));
    }
    else
    {
      cout << "ERROR: we already have part of a curved polygon, but the input file gives info for a circle??" << endl;
    }
    return;
  }
}

void Parser::initialize()
  {
  _writer.writeHeader();
  }

void Parser::finalize()
  {
  _writer.write(*getCurrentAirspace());
  curved_polygon = 0;
  }
