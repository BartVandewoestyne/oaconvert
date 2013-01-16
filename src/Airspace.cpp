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
  altitude_ceiling_in_meter(-1),
  floor_string(""),
  altitude_floor_in_meter(-1),
  curved_poly(),
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


const string& Airspace::getCeilingString() const
{
    return ceiling_string;
}


const string& Airspace::getFloorString() const
{
    return floor_string;
}


/**
  * Return the ceiling altitude in METER.
  */
double Airspace::getCeilingInMeter() const
{
    return altitude_ceiling_in_meter;
}


/**
  * Return the floor altitude in METER.
  */
double Airspace::getFloorInMeter() const
{
    return altitude_floor_in_meter;
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
    this->altitude_ceiling_in_meter = ceiling;
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
    this->altitude_floor_in_meter = floor;
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
    curved_poly.add(s);
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
    return StringUtils::hasSubstring(name, "CTR");
}


/**
 * Return true if this airspace is a TMZ (Transponder Mandatory Zone).  The
 * airspace will be a TMZ if its name contains the case sensitive string 'TMZ'.
 */
bool Airspace::isTMZ() const
{
    return StringUtils::hasSubstring(name, "TMZ");
}


/**
 * Return true if this airspace is an ATZ (Aerodrome Traffic Zone).  The
 * airspace will be an ATZ if its name contains the case sensitive string 'ATZ'.
 */
bool Airspace::isATZ() const
{
    return StringUtils::hasSubstring(name, "ATZ");
}


/**
  * Return true if this airspace is a CTA.  The airspace
  * will be a CTA if its name contains the case sensitive
  * string 'CTA'.
  */
bool Airspace::isCTA() const
{
    return StringUtils::hasSubstring(name, "CTA");
}


/**
  * Return true if this airspace is a TMA.  The airspace
  * will be a TMA if its name contains the case sensitive
  * string 'TMA'.
  */
bool Airspace::isTMA() const
{
    return StringUtils::hasSubstring(name, "TMA");
}


/**
  * Return true if this airspace is a Special Rule Zone (SRZ).  The airspace
  * is considered as a SRZ if its name contains the case sensitive string 'SRZ'.
  */
bool Airspace::isSRZ() const
{
    return StringUtils::hasSubstring(name, "SRZ");
}


/**
  * Return true if this airspace is 'floating', by which
  * we mean that its floor is above 0 m AMSL.
  */
bool Airspace::isFloating() const
{
    if ( getFloorInMeter() > 0 ) {
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
    return StringUtils::hasSubstring(name, "vectoring area");
}


/**
  * Return true if the activity of this airspace depends on NOTAMs.  This
  * will be the case if its name contains the case sensitive
  * string 'NOTAM' in its AN-record.
  */
bool Airspace::isByNOTAM() const
{
    return StringUtils::hasSubstring(name, "NOTAM");
}


/**
  * Return true if the activity of this airspace depends on an AUP (Airspace
  * Use Plan).  This will be the case if its name contains the case sensitive
  * string 'AUP' in its AN-record.
  */
bool Airspace::isByAUP() const
{
    return StringUtils::hasSubstring(name, "AUP");
}


/**
  * Return true if this airspace is a FIR.  The airspace
  * will be a FIR if its name contains the case sensitive
  * string 'FIR'.
  */
bool Airspace::isFIR() const
{
    return StringUtils::hasSubstring(name, "FIR");
}


/**
  * Return true if this airspace is a Low Flying Area.  The airspace
  * will be a Low Flying Area if its name contains the case sensitive
  * string 'LFA'.
  */
bool Airspace::isLowFlyingArea() const
{
    return StringUtils::hasSubstring(name, "LFA");
}


/**
  * Return true if this airspace is a Low Flying Area Golf.  The airspace
  * will be a Low Flying Area Golf if its name contains the case sensitive
  * string 'LOW FLYING AREA GOLF'.
  */
bool Airspace::isLowFlyingAreaGolf() const
{
    return StringUtils::hasSubstring(name, "LOW FLYING AREA GOLF");
}


/**
  * Return true if this airspace is a Low Flying Route.  The airspace
  * will be a Low Flying Area Route if its name contains the case sensitive
  * string 'LFR'.
  */
bool Airspace::isLowFlyingRoute() const
{
    return StringUtils::hasSubstring(name, "LFR");
}


/**
 * Return true if this airspace is an airway.  The airspace
 * will be an airway if its name contains the case sensitive
 * string 'Airway'.
 */
bool Airspace::isAirway() const
{
    return StringUtils::hasSubstring(name, "Airway");
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
  * Return true if this airspace is a Restricted area.  The airspace
  * will be a Restricted area if its class is the case sensitive
  * character 'R'.
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
    return StringUtils::hasSubstring(ceiling_string, "AGL");
}


/**
 * Return true if the AL-record contains a floor specification
 * in feet or meters Above Ground Level (AGL).
 */
bool Airspace::hasAGLFloor() const
{
    return StringUtils::hasSubstring(floor_string, "AGL");
}


/**
 * Return true if the AH-record contains a ceiling specification
 * in feet or meters SFC.
 */
bool Airspace::hasSFCCeiling() const
{
    return StringUtils::hasSubstring(ceiling_string, "SFC");
}


/**
 * Return true if the AL-record contains a floor specification
 * in feet or meters (SFC).
 */
bool Airspace::hasSFCFloor() const
{
    return StringUtils::hasSubstring(floor_string, "SFC");
}


/**
 * Return true if the AH-record contains a GND ceiling specification.
 */
bool Airspace::hasGNDCeiling() const
{
    return StringUtils::hasSubstring(ceiling_string, "GND");
}


/**
 * Return true if the AL-record contains a GND floor specification.
 */
bool Airspace::hasGNDFloor() const
{
    return StringUtils::hasSubstring(floor_string, "GND");
}


/**
 * Return true if the AL-record contains a floor specification
 * in Flight Level.
 */
bool Airspace::hasFLFloor() const
{
    return StringUtils::hasSubstring(floor_string, "FL");
}


/**
 *
 */
bool Airspace::hasAbsoluteCeiling() const
{

  if ( !( hasAGLCeiling() || hasSFCCeiling() || hasGNDCeiling() ) ) {
    return true;
  } else {
    return false;
  }
}


/**
 *
 */
bool Airspace::hasAbsoluteFloor() const
{

  if ( !( hasAGLFloor() || hasSFCFloor() || hasGNDFloor() ) ) {
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
    return curved_poly;
}


void Airspace::clear()
{
    name = "";
    clss = "";
    altitude_ceiling_in_meter = -1.0;
    altitude_floor_in_meter = -1.0;
    labels.clear();
}


bool Airspace::operator<(const Airspace& s) const
{
  std::string s1 = getName();
  std::string s2 = s.getName();
  return s1 < s2;
}


std::ostream& operator<<(std::ostream& out, const Airspace& s)
{
    out << "Airspace name:    " << s.getName() << endl;
    out << "Airspace class:   " << s.getClass() << endl;
    out << "Airspace ceiling: " << s.getCeilingInMeter() << endl;
    out << "Airspace floor:   " << s.getFloorInMeter() << endl;
    if ( !s.labels.empty() )
    {
        out << "Airspace label coordinates:" << endl;
        
        vector<Label>::const_iterator it;
        for (it=s.labels.begin(); it < s.labels.end(); ++it)
        {
            // TODO: seems like both work here???
            const Label label = *it;
            //const Label &label = *it;
            out << "  " << label.getText() << " -- " << label.getCoordinate() << endl;
        }
    }
    // TODO out  << "CurvedPolygon: " << s.p << endl;
    return out;
}
