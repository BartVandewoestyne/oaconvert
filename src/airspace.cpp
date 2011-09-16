#include <iostream>
#include <string>
#include "airspace.h"
#include "stringutils.h"
#include "parser.h"
using namespace std;

AirSpace::AirSpace()
{/* Body intentionally empty. */}

void AirSpace::setCeiling(string ceiling)
{
  this->ceiling = ceiling;
}

string AirSpace::getCeiling()
{
  return ceiling;
}

void AirSpace::setFloor(string floor)
{
  this->floor = floor;
}

string AirSpace::getFloor()
{
  return floor;
}

Polygon& AirSpace::getPolygon()
{
  return polygon;
}

void AirSpace::setName(string mystring)
{
  name = mystring;
}

string AirSpace::getName()
{
  return name;
}

void AirSpace::setClass(string clss)
{
  this->clss = clss;
}

string AirSpace::getClass()
{
  return clss;
}

void AirSpace::addLabelCoordinate(Coordinate c)
{
  labelCoordinates.push_back(c);
}

ostream& operator <<(ostream& outputStream, const AirSpace& s)
{
  outputStream << "Name:    " << s.name << endl;
  outputStream << "Class:   " << s.clss << endl;
  outputStream << "Ceiling: " << s.ceiling << endl;
  outputStream << "Floor:   " << s.floor << endl;
  if (s.labelCoordinates.size() > 0)
  {
    outputStream << "Label coordinates:" << endl;
    for (unsigned int i=0; i<s.labelCoordinates.size(); i++)
    {
      outputStream << "  " << s.labelCoordinates[i] << endl;
    }
  }
  outputStream << s.polygon << endl;
  return outputStream;
}

void AirSpace::clear()
{
    name = "";
    clss = "";
    ceiling = "";
    floor = "";
    polygon.clear();
    labelCoordinates.clear();
}
