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
#include "Arc.h"
#include "Point.h"
#include "CurvedPolygon.h"
#include "GeometricShape.h"
#include "Parser.h"
#include "StringUtils.h"
#include "Label.h"

using namespace std;

Airspace::Airspace()
{}


Airspace::~Airspace()
{
}


const string& Airspace::getName() const
{
    return name;
}


const string& Airspace::getClass() const
{
    return clss;
}


/**
  * Return the ceiling altitude in METER.
  */
const double Airspace::getCeiling() const
{
    return ceiling;
}


/**
  * Return the floor altitude in METER.
  */
const double Airspace::getFloor() const
{
    return floor;
}


void Airspace::setName(const string& mystring)
{
    name = mystring;
}


void Airspace::setClass(const string& clss)
{
    this->clss = clss;
}


/**
  * Set the ceiling altitude in METER.
  */
void Airspace::setCeiling(const double ceiling)
{
    this->ceiling = ceiling;
}


/**
  * Set the floor altitude in METER.
  */
void Airspace::setFloor(const double floor)
{
    this->floor = floor;
}


/**
  * Add the specified GeometricShape to this Airspace's internal
  * representation.  Allowed GeometricShapes are Point, Arc and Circle.
  *
  * TODO:
  *   * if stuff is already present, then Circle should not be
  *     allowed
  *   * if a Circle is already present, then we should
  *     not be able to add stuff.
  */
void Airspace::add(const GeometricShape* s)
{
    p.add(s);
}


void Airspace::add(const Label& label)
{
    labels.push_back( label );
}


/**
  * Return true if this airspace is a CTR.  The airspace
  * will be a CTR if its name contains the case sensitive
  * string 'CTR'.
  *
  * Note:
  *   In the OpenAir format, you can also specify 'CTR' in the
  *   AC-record, so we could also check for that... but the problem
  *   with this approach is that some CTR's have 'AC C' or 'AC D' in their
  *   AC-record... so if we put 'AC CTR' there, we lose that information.
  */
const bool Airspace::isCTR() const
{
    size_t found = name.find("CTR");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a CTA.  The airspace
  * will be a CTA if its name contains the case sensitive
  * string 'CTA'.
  */
const bool Airspace::isCTA() const
{
    size_t found = name.find("CTA");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a TMA.  The airspace
  * will be a TMA if its name contains the case sensitive
  * string 'TMA'.
  */
const bool Airspace::isTMA() const
{
    size_t found = name.find("TMA");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a vectoring area.  The airspace
  * will be a vectoring area if its name contains the case sensitive
  * string 'vectoring area'.
  */
const bool Airspace::isVectoringArea() const
{
    size_t found = name.find("vectoring area");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a FIR.  The airspace
  * will be a FIR if its name contains the case sensitive
  * string 'FIR'.
  */
const bool Airspace::isFIR() const
{
    size_t found = name.find("FIR");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a Low Flying Area Golf.  The airspace
  * will be a Low Flying Area Golf if its name contains the case sensitive
  * string 'LOW FLYING AREA GOLF'.
  */
const bool Airspace::isLowFlyingAreaGolf() const
{
    size_t found = name.find("LOW FLYING AREA GOLF");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a Prohibited area.  The airspace
  * will be a Prohibited area if its class is the case sensitive
  * character 'P'.
  */
const bool Airspace::isProhibited() const
{
    if ( clss.compare("P") == 0) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a Prohibited area.  The airspace
  * will be a Prohibited area if its class is the case sensitive
  * character 'P'.
  */
const bool Airspace::isRestricted() const
{
    if ( clss.compare("R") == 0) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is a Danger area.  The airspace
  * will be a Danger area if its class is the case sensitive
  * character 'Q'.
  */
const bool Airspace::isDanger() const
{
    if ( clss.compare("Q") == 0) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return the (non-discretized!) curved polygon object
  * representing this Airspace.
  */
const CurvedPolygon& Airspace::getCurvedPolygon() const
{
    return p;
}


void Airspace::clear()
{
    name = "";
    clss = "";
    ceiling = -1.0;
    floor = -1.0;
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
            const Label &label = s.labels[i];
            outputStream << "  " << label.getText() << " -- " << label.getCoordinate() << endl;
        }
    }
    // TODO outputStream  << "CurvedPolygon: " << s.p << endl;
    return outputStream;
}
