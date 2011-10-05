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

TODO: THIS FILE IS NOT WORKING YET!!! WAS COPY PASTE FROM Airspace.cpp!
#include <iostream>
#include <string>
#include "coordinate.h"
using namespace std;

Label::Label(string text, Coordinate c)
{
  this->text = text;
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

/**
 * Return the Polygon that contains all Coordinates defining this airspace.
 */
const Polygon& Airspace::getPolygon() const
{
  return polygon;
}

Polygon& Airspace::getPolygon()
{
  return polygon;
}

const Circle& Airspace::getCircle() const
{
  return circle;
}

Circle& Airspace::getCircle()
{
  return circle;
}

const Arc& Airspace::getArc() const
{
  return arc;
}

Arc& Airspace::getArc()
{
  return arc;
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

/**
 * Return true if the airspace is defined by a Polygon (some airspaces are
 * only defined by a circle and don't have Polygon points).
 */
bool Airspace::hasPolygon() const
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

/**
 * Return true if the airspace is defined by a Circle (and airspace can be
 * defined by a circle or a polygon).
 */
bool Airspace::hasCircle() const
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

/**
 * Each airspace can have multiple name-labels that each have their location
 * on a map.  With this method, you can add locations for these labels.
 */
void Airspace::addLabelCoordinate(const Coordinate& c)
{
  labelCoordinates.push_back(c);
}

void Airspace::clear()
{
  name = "";
  clss = "";
  ceiling = "";
  floor = "";
  polygon.clear();
  circle.invalidate();
  arc.invalidate();
  labelCoordinates.clear();
}

ostream& operator <<(ostream& outputStream, const Airspace& s)
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
  return outputStream;
}
