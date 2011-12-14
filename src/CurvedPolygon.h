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

#ifndef CURVEDPOLYGON_H
#define CURVEDPOLYGON_H

#include "GeometricShape.h"

class Coordinate;
class GeometricShape;
class OutputState;

class CurvedPolygon
{
public:

    CurvedPolygon();
    virtual ~CurvedPolygon();

    void add( const GeometricShape* s );

    virtual void write( std::ostream& stream, const OutputState* outputstate ) const;
    virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const;
    friend std::ostream& operator <<(std::ostream& outputStream, const CurvedPolygon& p);

private:

    std::vector<const GeometricShape*> shapes;

    // copy-constructor is private and not implemented (yet...)!!!
    CurvedPolygon( const CurvedPolygon& i_other );

};

#endif /* CURVEDPOLYGON_H */
