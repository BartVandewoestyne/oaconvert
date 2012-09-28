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

#include <iostream>
#include "Point.h"
#include "Coordinate.h"

using namespace std;

Point::Point()
    : m_coordinate()
{}


Point::Point( const Coordinate& c )
    : m_coordinate( c )
{}


const Coordinate& Point::getCoordinate() const
{
    return m_coordinate;
}


void Point::discretize( std::vector<Coordinate>& coords, double ) const
{
    coords.push_back( m_coordinate );
}


ostream& operator<<(ostream& out, const Point& point)
{
    out << "Point (" << point.getCoordinate() << ")";
    return out;
}
