#include <iostream>
#include <boost/regex.hpp>
#include "parser.h"
#include "airspace.h"
using namespace boost;

Parser::Parser():currentAirSpace()
{
  //currentAirSpace = AirSpace(); // not necessary???
}

void Parser::setCurrentAirspace(AirSpace s)
{
  currentAirSpace = s;
}

AirSpace& Parser::getCurrentAirSpace()
{
  return currentAirSpace;
}

Coordinate Parser::getCoordinate(std::string s)
{
  smatch matches;
  regex expression;

  expression = "[^0-9]*(\\d+):(\\d\\d):(\\d\\d)\\s*([NZOWSEnzowse])\\s+(\\d+):(\\d\\d):(\\d\\d)\\s([NZOWSEnzowse])*.*";
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

    Latitude lat(atoi(degreesLat.c_str()),
                 atoi(minutesLat.c_str()),
                 atoi(secondsLat.c_str()), directionLat[0]);
    Longitude lon(atoi(degreesLon.c_str()),
                  atoi(minutesLon.c_str()),
                  atoi(secondsLon.c_str()), directionLon[0]);
    return Coordinate(lat, lon);
  }

  cout << "\nNo valid coordinate definition found!!" << endl;
  exit(1);
}

void Parser::handleLine(std::string line)
{

  smatch matches;
  regex expression;

  expression = "\\s*\\*.*";
  if ( regex_match(line, matches, expression) )
  {
    // do nothing.
  }

  expression = "\\s*AC\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {

    cout << getCurrentAirSpace() << endl;
    getCurrentAirSpace().clear();

    string airspace_class;
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      airspace_class.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirSpace().setClass(airspace_class);

  }

  expression = "\\s*AN\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string airspace_name;
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      airspace_name.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirSpace().setName(airspace_name);
    // BUG: Why doesn't this work???
  }

  expression = "\\s*AH\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string airspace_ceiling;
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      airspace_ceiling.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirSpace().setCeiling(airspace_ceiling);
  }

  expression = "\\s*AL\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string airspace_floor;
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      airspace_floor.assign(matches[i].first, matches[i].second);
    }
    getCurrentAirSpace().setFloor(airspace_floor);
  }

  expression = "\\s*AT\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    string airspace_coordinate;
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      airspace_coordinate.assign(matches[i].first, matches[i].second);
    }
    //getCurrentAirSpace().addPoint(airspace_coordinate);
  }

}
