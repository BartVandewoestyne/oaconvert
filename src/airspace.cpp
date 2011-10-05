#include <cassert>
#include <iostream>
#include <string>

#include "airspace.h"
#include "Circle.h"
#include "CurvedPolygon.h"
#include "Region.h"
#include "parser.h"
#include "stringutils.h"

using namespace std;

AirSpace::AirSpace()
: region(0)
{}

AirSpace::~AirSpace()
{
  delete region;
}

const string& AirSpace::getName() const
{
  return name;
}

const string& AirSpace::getClass() const
{
  return clss;
}

const string& AirSpace::getCeiling() const
{
  return ceiling;
}

const string& AirSpace::getFloor() const
{
  return floor;
}

const Region* AirSpace::getRegion() const
{
  return region;
}

void AirSpace::setName(const string& mystring)
{
  name = mystring;
}

void AirSpace::setClass(const string& clss)
{
  this->clss = clss;
}

void AirSpace::setCeiling(const string& ceiling)
{
  this->ceiling = ceiling;
}

void AirSpace::setFloor(const string& floor)
{
  this->floor = floor;
}

//void AirSpace::add( Region* region )
//{
//  this->region = region;
//}


Circle* AirSpace::addCircle(const Coordinate& coordinate, double radius)
{
//  assert(!region); // not initialized yet
  Circle *result = new Circle(coordinate, radius);
  region = result;
  return result;
}

CurvedPolygon* AirSpace::addCurvedPolygon()
{
//  assert(!region); // not initialized yet
  CurvedPolygon *result = new CurvedPolygon();
  region = result;
  return result;
}

void AirSpace::addLabelCoordinate(const std::string& label, const Coordinate& c)
{
  labelCoordinates.push_back( label_type( label, c ) );
}

void AirSpace::clear()
{
  name = "";
  clss = "";
  ceiling = "";
  floor = "";
  labelCoordinates.clear();
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
    for (size_t i=0; i<s.labelCoordinates.size(); ++i)
    {
      const AirSpace::label_type &label = s.labelCoordinates[i];
      outputStream << "  " << label.first << " -- " << label.second << endl;
    }
  }
  s.region->print( outputStream );
  return outputStream;
}
