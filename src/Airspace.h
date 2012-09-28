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

#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <string>
#include <utility>
#include <vector>

#include "Point.h"
#include "Circle.h"
#include "Arc.h"
#include "CurvedPolygon.h"
#include "Label.h"

class Point;
class Circle;
class Arc;
class CurvedPolygon;
class Region;

class Airspace
{

private:

    // Name of the airspace.
    std::string name;

    // Class of the airspace (CTR, TMA, Q (Prohibited), R (Restricted), ...)
    //
    // Note: some airspaces can have several classes.  In this case, the classes
    //       are specified with forward slashes in between them and without
    //       spaces, e.g. 'AC C/E'.
    std::string clss;

    // Ceiling string
    std::string ceiling_string;

    //! Ceiling altitude in METER.
    double altitude_ceiling_in_meter;

    // Floor string
    std::string floor_string;

    //! Floor altitude in METER.
    double altitude_floor_in_meter;

    //! Closed curved polygon defining the airspace.
    CurvedPolygon curved_poly;

    //! Collection of string labels with associated position.
    std::vector<Label> labels;

public:

    Airspace();
    ~Airspace();

    const std::string& getName() const;
    const std::string& getClass() const;
    const std::string& getCeilingString() const;
    const std::string& getFloorString() const;
    double getCeilingInMeter() const;
    double getFloorInMeter() const;
    const CurvedPolygon& getCurvedPolygon() const;

    void setName(const std::string& mystring);
    void setClass(const std::string& clss);
    void setCeilingString(const std::string& ceiling_string);
    void setCeiling(const double ceiling);
    void setFloorString(const std::string& floor_string);
    void setFloor(const double floor);

    void add(const GeometricShape* s);

    bool isFIR() const;
    bool isCTR() const;
    bool isATZ() const;
    bool isCTA() const;
    bool isTMA() const;
    bool isSRZ() const;
    bool isTMZ() const;
    bool isFloating() const;
    bool isVectoringArea() const;
    bool isByNOTAM() const;
    bool isByAUP() const;
    bool isLowFlyingRoute() const;
    bool isAirway() const;
    bool isLowFlyingArea() const;
    bool isLowFlyingAreaGolf() const;
    bool isProhibited() const;
    bool isRestricted() const;
    bool isDanger() const;
    bool hasAGLCeiling() const;
    bool hasAGLFloor() const;
    bool hasSFCCeiling() const;
    bool hasSFCFloor() const;
    bool hasGNDCeiling() const;
    bool hasGNDFloor() const;
    bool hasFLCeiling() const;
    bool hasFLFloor() const;
    bool hasAbsoluteCeiling() const;
    bool hasAbsoluteFloor() const;

    /**
     * Each airspace can have multiple name-labels that each have their location
     * on a map.  With this method, you can add such labels.
     */
    void add(const Label& label);

    void clear();

    friend std::ostream& operator<<(std::ostream& out, const Airspace& s);

};

#endif /* AIRSPACE_H */
