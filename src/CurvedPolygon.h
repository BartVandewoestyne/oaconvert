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

#include "Region.h"

class Arc;
class Coordinate;
class Segment;

class CurvedPolygon : public Region
{
public:
    CurvedPolygon();
    virtual ~CurvedPolygon();

    void addArc( const Arc& arc );
    // TODO (question Bart): shouldn't we jusd change addLinearSegment to addPoint because
    //      a CurvedPolygon in essence is a set of arcs and points (connected by line segments)???
    void addLinearSegment( const Coordinate& point );

    //////////////////////////////////////////////////
    // Interface Region
    //! @copydoc Region::write
    virtual void write( std::ostream& stream, const OutputState* outputstate ) const;

    //! @copydoc Region::discretize
    virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const;

    //! @copydoc Region::print
    virtual std::ostream& print( std::ostream &stream );

private:
    // copy-constructor is private and not implemented (yet...)!!!
    CurvedPolygon( const CurvedPolygon& i_other );

private:
    std::vector<Segment*> m_segments;

};



#endif /* end of include guard: CURVEDPOLYGON_H */
