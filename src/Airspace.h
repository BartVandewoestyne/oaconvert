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

#include "Coordinate.h"

class Circle;
class CurvedPolygon;
class Region;

class Airspace {

  public:

    typedef std::pair<std::string,Coordinate> label_type;

  private:

    std::string name;
    std::string clss;

    // TODO: probably, these should change to doubles (representing stuff in metres).
    std::string ceiling;
    std::string floor;

    //! Closed region defining the airspace.
    Region* region;

    //! Collection of string labels with associated position.
    std::vector<label_type> labels;

  public:

    Airspace();
    ~Airspace();

    const std::string& getName() const;
    const std::string& getClass() const;
    const std::string& getCeiling() const;
    const std::string& getFloor() const;
    const Region* getRegion() const;

    void setName(const std::string& mystring);
    void setClass(const std::string& clss);
    void setCeiling(const std::string& ceiling);
    void setFloor(const std::string& floor);

//    /**
//     * Add the region to this airspace (and pass ownership of the pointer).
//     */
//    void add( Region* region );
    

    /**
     * Add a circle region to this airspace and return a pointer to the newly created
     * object. The ownership remains with this airspace.
     */
    Circle* addCircle(const Coordinate& coordinate, double radius);

    /**
     * Add a curved polygon region to this airspace and return a pointer to the newly created
     * object. The ownership remains with this airspace.
     */
    CurvedPolygon* addCurvedPolygon();

    /**
     * Each airspace can have multiple name-labels that each have their location
     * on a map.  With this method, you can add locations for these labels.
     */
    void addLabelCoordinate(const std::string& label, const Coordinate& c);

    void clear();

    friend std::ostream& operator <<(std::ostream& outputStream, const Airspace& l);

};

#endif /* AIRSPACE_H */
