#include <iostream>
#include <boost/regex.hpp>
#include "parser.h"
using namespace boost;

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
  cout << deg_string << endl;
  deg = atoi(deg_string.c_str());

  pos3 = s.find_first_of(":", pos2+1);
  min_string = s.substr(pos2+1, 2);
  cout << min_string << endl;
  min = atoi(min_string.c_str());

  sec_string = s.substr(pos2+4, 2);
  cout << sec_string << endl;
  sec = atoi(sec_string.c_str());

  direction = s[pos2+7];
  cout << direction << endl;

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
    cout << "COMMENT LINE MATCH" << endl;
  }

  expression = "\\s*AC\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    cout << "AC LINE MATCH" << endl;
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      string airspace_class(matches[i].first, matches[i].second);
      cout << "\tAirspace class: " << airspace_class << endl;
    }
  }

  expression = "\\s*AN\\s+(.*)";
  if ( regex_match(line, matches, expression) )
  {
    cout << "AN LINE MATCH" << endl;
    for (unsigned int i = 1; i < matches.size(); i++)
    {
      string airspace_name(matches[i].first, matches[i].second);
      cout << "\tAirspace name: " << airspace_name << endl;
    }
  }

}
