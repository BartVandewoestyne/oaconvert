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

#include "CurvedPolygon.h"
#include "GeometricShape.h"
#include "Coordinate.h"
#include "Point.h"
#include "OutputState.h"


CurvedPolygon::CurvedPolygon()
    : shapes()
{}

CurvedPolygon::~CurvedPolygon()
{
    std::vector<const GeometricShape*>::iterator it;
    for ( it=shapes.begin(); it < shapes.end(); it++ )
    {
      delete *it;
    }
    shapes.clear();
}

void CurvedPolygon::add( const GeometricShape* s )
{
    shapes.push_back( s );
}


void CurvedPolygon::discretize( std::vector<Coordinate>& coords, double resolution ) const
{
    coords.clear();
    for( size_t i = 0; i < shapes.size(); ++i )
    {
        shapes[i]->discretize( coords, resolution );
    }
}


std::ostream& operator <<(std::ostream& outputStream, const CurvedPolygon& p)
{
    outputStream << "Curved Polygon:";
    for( size_t i = 0; i < p.shapes.size(); ++i )
    {
        outputStream << "  " << p.shapes[i] << std::endl;
    }

    return outputStream;
}
