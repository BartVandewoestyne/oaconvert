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

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <stdlib.h>

#include "Coordinate.h"
#include "GeometricShape.h"

class Point : public GeometricShape
{
public:

    Point();
    Point( const Coordinate& c );
    virtual ~Point() {};

    const Coordinate& getCoordinate() const;

    virtual void discretize( std::vector<Coordinate>& coords, double ) const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Point& c);

private:
    Coordinate m_coordinate;
};

#endif /* POINT_H */
