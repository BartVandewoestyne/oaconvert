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
#include <cmath>
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
: name(""),
  clss(""),
  ceiling_string(""),
  ceiling(-1),
  floor_string(""),
  floor(-1),
  p(),
  labels()
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
double Airspace::getCeiling() const
{
    return ceiling;
}


/**
  * Return the floor altitude in METER.
  */
double Airspace::getFloor() const
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


void Airspace::setCeilingString(const string& ceiling_string)
{
    this->ceiling_string = ceiling_string;
}


/**
  * Set the ceiling altitude in METER.
  */
void Airspace::setCeiling(const double ceiling)
{
    this->ceiling = ceiling;
}


void Airspace::setFloorString(const string& floor_string)
{
    this->floor_string = floor_string;
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
bool Airspace::isCTR() const
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
bool Airspace::isCTA() const
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
bool Airspace::isTMA() const
{
    size_t found = name.find("TMA");
    if ( found != string::npos ) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this airspace is 'floating', by which
  * we mean that its floor is above 0 m AMSL.
  */
bool Airspace::isFloating() const
{
    if ( getFloor() > 0 ) {
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
bool Airspace::isVectoringArea() const
{
    size_t found = name.find("vectoring area");
    if ( found != string::npos ) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if the activity of this airspace depends on NOTAMs.  This
  * will be the case if its name contains the case sensitive
  * string 'NOTAM' in its AN-record.
  */
bool Airspace::isByNOTAM() const
{
    size_t found = name.find("NOTAM");
    if ( found != string::npos ) {
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
bool Airspace::isFIR() const
{
    size_t found = name.find("FIR");
    if ( found != string::npos ) {
      return true;
    } else {
      return false;
    }
}


/**
  * Return true if this 'airspace' represents the edges
  * of the map.  An airspace is the map edge if it contains
  * the case sensitive string 'Map edge'.
  */
bool Airspace::isMapEdge() const
{
    size_t found = name.find("Map edge");
    if (found != string::npos ) {
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
bool Airspace::isLowFlyingAreaGolf() const
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
bool Airspace::isProhibited() const
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
bool Airspace::isRestricted() const
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
bool Airspace::isDanger() const
{
    if ( clss.compare("Q") == 0) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return true if the AH-record contains a ceiling specification
 * in feet or meters Above Ground Level (AGL).
 */
bool Airspace::hasAGLCeiling() const
{
    size_t found = ceiling_string.find("AGL");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return true if the AL-record contains a floor specification
 * in feet or meters Above Ground Level (AGL).
 */
bool Airspace::hasAGLFloor() const
{
    size_t found = floor_string.find("AGL");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return true if the AH-record contains a ceiling specification
 * in feet or meters SFC.
 */
bool Airspace::hasSFCCeiling() const
{
    size_t found = ceiling_string.find("SFC");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return true if the AL-record contains a floor specification
 * in feet or meters (SFC).
 */
bool Airspace::hasSFCFloor() const
{
    size_t found = floor_string.find("SFC");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return true if the AL-record contains a GND floor specification.
 */
bool Airspace::hasGNDFloor() const
{
    size_t found = floor_string.find("GND");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return true if the AH-record contains a ceiling specification
 * in Flight Level.
 */
bool Airspace::hasFLCeiling() const
{
    size_t found = ceiling_string.find("FL");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return true if the AL-record contains a floor specification
 * in Flight Level.
 */
bool Airspace::hasFLFloor() const
{
    size_t found = floor_string.find("FL");
    if ( found != string::npos) {
      return true;
    } else {
      return false;
    }
}


/**
 * Return a label for this airspace for a 2D map representation.
 */
const string Airspace::get2DLabel() const
{
    string label2D;

    if ( isTMA() ) {
        label2D.append("TMA:");
    }
    if ( isCTA() ) {
        label2D.append("CTA:");
    }
    if ( isProhibited() ) {
        label2D.append("Prohibited:");
    }
    if ( isVectoringArea() ) {
        label2D.append("Vectoring Area:");
    }
    if ( isByNOTAM() ) {
        label2D.append("By NOTAM:");
    }
    if ( (   isTMA()
          || isCTA()
          || isVectoringArea()
          || isByNOTAM()
          || isProhibited() ) && (getFloor() > 0) ) {

        string myName(getName());
        if (isByNOTAM()) {
          myName = myName.substr(10);
        }
        if (hasAGLFloor()) {
            //label2D.append(" " + floor(getFloor()) + " m AGL max"); // TODO
        } else if (hasFLFloor()) {
            //label2D.append(" " + floor(getFloor()) + " m (+QNH) max");
        } else {
            //label2D.append(" " + floor(getFloor()) + " m max");
        }
        label2D.append(" (" + myName + ")");

    } else {
      label2D.append(getName());
    }

    return label2D;

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
