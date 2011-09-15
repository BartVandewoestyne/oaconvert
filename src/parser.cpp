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

  int pos1, pos2, pos3;
  int deg, min, sec;
  char direction;
  string deg_string, min_string, sec_string;

  pos1 = s.find_first_of(":");
  deg_string = s.substr(0, pos1);
  deg = atoi(deg_string.c_str());

  pos2 = s.find_first_of(":", pos1+1);
  min_string = s.substr(pos1+1, 2);
  min = atoi(min_string.c_str());

  pos3 = s.find_first_of(" ", pos2+1);
  sec_string = s.substr(pos2+1, 2);
  sec = atoi(sec_string.c_str());

  direction = s[pos3+1];

  Latitude lat(deg, min, sec, direction);


  pos1 = pos3+3;
  pos2 = s.find_first_of(":", pos1+1);
  deg_string = s.substr(pos1, pos2-pos1);
  deg = atoi(deg_string.c_str());

  pos3 = s.find_first_of(":", pos2+1);
  min_string = s.substr(pos2+1, 2);
  min = atoi(min_string.c_str());

  sec_string = s.substr(pos2+4, 2);
  sec = atoi(sec_string.c_str());

  direction = s[pos2+7];

  Longitude lon(deg, min, sec, direction);

  return Coordinate(lat, lon);

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
