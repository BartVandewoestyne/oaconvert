#include <iostream>
#include <string>
#include "airspace.h"
#include "stringutils.h"
#include "parser.h"
using namespace std;

AirSpace::AirSpace()
{
  //cout << "AirSpace()" << endl;
}

void AirSpace::setCeiling(const string& ceiling)
{
  this->ceiling = ceiling;
}

const string& AirSpace::getCeiling() const
{
  return ceiling;
}

void AirSpace::setFloor(const string& floor)
{
  this->floor = floor;
}

const string& AirSpace::getFloor() const
{
  return floor;
}

const Polygon& AirSpace::getPolygon() const
{
  return polygon;
}

Polygon& AirSpace::getPolygon()
{
  return polygon;
}

bool AirSpace::hasPolygon() const
{
  if (polygon.getNbPoints() > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool AirSpace::hasCircle() const
{
  if ( circle.isValid() )
  {
    //cout << "DEBUG: airspace has a circle" << endl;
    return true;
  }
  else
  {
    //cout << "DEBUG: airspace doesn't have a circle" << endl;
    return false;
  }
}

const Circle& AirSpace::getCircle() const
{
  return circle;
}

Circle& AirSpace::getCircle()
{
  return circle;
}

void AirSpace::setName(const string& mystring)
{
  name = mystring;
}

const string& AirSpace::getName() const
{
  return name;
}

void AirSpace::setClass(const string& clss)
{
  this->clss = clss;
}

const string& AirSpace::getClass() const
{
  return clss;
}

void AirSpace::addLabelCoordinate(const Coordinate& c)
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
    circle.invalidate();
    labelCoordinates.clear();
}
