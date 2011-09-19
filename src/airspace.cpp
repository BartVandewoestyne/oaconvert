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

string AirSpace::getCeiling() const
{
  return ceiling;
}

void AirSpace::setFloor(string floor)
{
  this->floor = floor;
}

string AirSpace::getFloor() const
{
  return floor;
}

Polygon& AirSpace::getPolygon()
{
  return polygon;
}

Circle& AirSpace::getCircle()
{
  return circle;
}

void AirSpace::setName(string mystring)
{
  name = mystring;
}

string AirSpace::getName() const
{
  return name;
}

void AirSpace::setClass(string clss)
{
  this->clss = clss;
}

string AirSpace::getClass() const
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
    for (unsigned int i=0; i<s.labelCoordinates.size(); ++i)
    {
      outputStream << "  " << s.labelCoordinates[i] << endl;
    }
  }
  outputStream << s.polygon << endl;
  outputStream << s.circle << endl;
  //s.circle.toPolish( outputStream );
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
