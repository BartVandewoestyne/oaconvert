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

#ifndef OUTPUTSTATE_H 
#define OUTPUTSTATE_H 

#include <iostream>
#include "Region.h"

class Airspace;
class Circle;
class CurvedPolygon;

class OutputState {

  public:

    OutputState(){};

    virtual void writeHeader(std::ostream &out) const = 0;
    virtual void writeFooter(std::ostream &out) const = 0;

    //! Use this method to write out an airspace.
    virtual void write(std::ostream& stream, const Airspace& airspace) const = 0;

    //! Helper methods to write out the info of an airspace.
    void write(std::ostream& stream, const Region* region) const;
    virtual void write(std::ostream& stream, const Circle* circle) const = 0;
    virtual void write(std::ostream& stream, const CurvedPolygon* curved_polygon) const = 0;

//    virtual void write(std::ostream &out, const Airspace& s) const = 0;
//    virtual void write(std::ostream &out, const Coordinate& c) const = 0;
//    virtual void write(std::ostream &out, const Polygon& p, const std::string &label) const = 0;
};


inline void OutputState::write(std::ostream& stream, const Region* region) const
{
  if( region )
  {
    region->write(stream, this);
  }
  else
  {
    std::cout << " WARNING: Not printing airspace with empty region." << std::endl;
  }
}

#endif /* OUTPUTSTATE_H */
