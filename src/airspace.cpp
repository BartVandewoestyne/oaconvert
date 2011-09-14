#include <iostream>
#include <string>
#include "airspace.h"
#include "stringutils.h"
#include "parser.h"
using namespace std;

AirSpace::AirSpace()
{
  cout << "Airspace default constructor: " << this << endl;
}

void AirSpace::setCeiling(string ceiling) {
  this->ceiling = ceiling;
}

string AirSpace::getCeiling() {
  return ceiling;
}

void AirSpace::setFloor(string floor) {
  this->floor = floor;
}

string AirSpace::getFloor() {
  return floor;
}

void AirSpace::setName(string mystring) {
  name = mystring;
}

string AirSpace::getName() {
  return name;
}

void AirSpace::setClass(string clss) {
  this->clss = clss;
}

string AirSpace::getClass() {
  return clss;
}

void AirSpace::addPoint(Point p) {

  points.push_back(p);

}

void AirSpace::handleLine(string line) {

  StringUtils s;

  string token="AN";
  if ( s.startsWith(line, token) )
  {
    setName(line.substr(3, line.length()));
  }

  token="AH";
  if ( s.startsWith(line, token) )
  {
    setCeiling(line.substr(3, line.length()));
  }

  token="AL";
  if ( s.startsWith(line, token) )
  {
    setFloor(line.substr(3, line.length()));
  }

  token="AT";
  if ( s.startsWith(line, token) )
  {
    // TODO: add labels on map.
  }

  token="V"; // variable assignment
  if ( s.startsWith(line, token) )
  {
    char variableName = line[2];
    cout << "variable name: " << variableName << endl;
    string variableValue = line.substr(4, line.length());
    cout << "variable Value: " << variableValue << endl;
  }

  token="DP";
  if ( s.startsWith(line, token) )
  {
    Parser p;
    Coordinate c = p.getCoordinate(line.substr(3, line.length()));
  }
  
}

ostream& operator <<(ostream& outputStream, const AirSpace& s)
{
  outputStream << "Name:    " << s.name << endl;
  outputStream << "Class:   " << s.clss << endl;
  outputStream << "Ceiling: " << s.ceiling << endl;
  outputStream << "Floor:   " << s.floor << endl;
  return outputStream;
}

void AirSpace::clear() {

    name = "";
    clss = "";
    ceiling = "";
    floor = "";
    //Coordinate *coordPtr;
    points.clear();

}
