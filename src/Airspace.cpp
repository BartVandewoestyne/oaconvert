/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.
  
  This file is part of oaconvert.
  
  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cassert>
#include <iostream>
#include <string>

#include "Airspace.h"
#include "Circle.h"
#include "CurvedPolygon.h"
#include "Region.h"
#include "Parser.h"
#include "StringUtils.h"

using namespace std;

Airspace::Airspace()
: region(0)
{}

Airspace::~Airspace()
{
  delete region;
}

const string& Airspace::getName() const
{
  return name;
}

const string& Airspace::getClass() const
{
  return clss;
}

const string& Airspace::getCeiling() const
{
  return ceiling;
}

const string& Airspace::getFloor() const
{
  return floor;
}

const Region* Airspace::getRegion() const
{
  return region;
}

void Airspace::setName(const string& mystring)
{
  name = mystring;
}

void Airspace::setClass(const string& clss)
{
  this->clss = clss;
}

void Airspace::setCeiling(const string& ceiling)
{
  this->ceiling = ceiling;
}

void Airspace::setFloor(const string& floor)
{
  this->floor = floor;
}

//void Airspace::add( Region* region )
//{
//  this->region = region;
//}


Circle* Airspace::addCircle(const Coordinate& coordinate, double radius)
{
//  assert(!region); // not initialized yet
  Circle *result = new Circle(coordinate, radius);
  region = result;
  return result;
}

CurvedPolygon* Airspace::addCurvedPolygon()
{
//  assert(!region); // not initialized yet
  CurvedPolygon *result = new CurvedPolygon();
  region = result;
  return result;
}

void Airspace::addLabelCoordinate(const std::string& label, const Coordinate& c)
{
  labels.push_back( label_type( label, c ) );
}

void Airspace::clear()
{
  name = "";
  clss = "";
  ceiling = "";
  floor = "";
  labels.clear();
}

ostream& operator <<(ostream& outputStream, const Airspace& s)
{
  outputStream << "Name:    " << s.name << endl;
  outputStream << "Class:   " << s.clss << endl;
  outputStream << "Ceiling: " << s.ceiling << endl;
  outputStream << "Floor:   " << s.floor << endl;
  if (s.labels.size() > 0)
  {
    outputStream << "Label coordinates:" << endl;
    for (size_t i=0; i<s.labels.size(); ++i)
    {
      const Airspace::label_type &label = s.labels[i];
      outputStream << "  " << label.first << " -- " << label.second << endl;
    }
  }
  s.region->print( outputStream );
  return outputStream;
}
