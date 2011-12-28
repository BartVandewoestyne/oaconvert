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

public:

private:

    // Name of the airspace.
    std::string name;

    // Class of the airspace (CTR, TMA, Prohibited, Restricted, ...)
    std::string clss;

    // Ceiling string
    std::string ceiling_string;

    //! Ceiling altitude in METER.
    double ceiling;

    // Floor string
    std::string floor_string;

    //! Floor altitude in METER.
    double floor;

    //! Closed curved polygon defining the airspace.
    CurvedPolygon p;

    //! Collection of string labels with associated position.
    std::vector<Label> labels;

public:

    Airspace();
    ~Airspace();

    const std::string& getName() const;
    const std::string& getClass() const;
    const double getCeiling() const;
    const double getFloor() const;
    const CurvedPolygon& getCurvedPolygon() const;

    void setName(const std::string& mystring);
    void setClass(const std::string& clss);
    void setCeilingString(const std::string& ceiling_string);
    void setCeiling(const double ceiling);
    void setFloorString(const std::string& floor_string);
    void setFloor(const double floor);

    void add(const GeometricShape* s);

    const bool isFIR() const;
    const bool isMapEdge() const;
    const bool isCTR() const;
    const bool isCTA() const;
    const bool isTMA() const;
    const bool isFloating() const;
    const bool isVectoringArea() const;
    const bool isByNOTAM() const;
    const bool isLowFlyingAreaGolf() const;
    const bool isProhibited() const;
    const bool isRestricted() const;
    const bool isDanger() const;
    const bool hasAGLFloor() const;
    const bool hasFLFloor() const;

    /**
     * Each airspace can have multiple name-labels that each have their location
     * on a map.  With this method, you can add such labels.
     */
    void add(const Label& label);

    void clear();

    friend std::ostream& operator <<(std::ostream& outputStream, const Airspace& l);

};

#endif /* AIRSPACE_H */
