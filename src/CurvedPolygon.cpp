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

#include "Arc.h"
#include "Coordinate.h"
#include "LinearSegment.h"
#include "OutputState.h"


CurvedPolygon::CurvedPolygon()
  {
  }

CurvedPolygon::~CurvedPolygon()
  {
  for( size_t i = 0; i < m_segments.size(); ++i )
    {
    delete m_segments[i];
    }
  m_segments.clear();
  }

void CurvedPolygon::addArc( const Arc& arc )
  {
  m_segments.push_back( new Arc( arc ) );
  }

void CurvedPolygon::addLinearSegment( const Coordinate& point )
  {
  m_segments.push_back( new LinearSegment( point ) );
  }

void CurvedPolygon::write( std::ostream& stream, const OutputState* outputstate ) const
  {
  outputstate->write( stream, this );
  }

void CurvedPolygon::discretize( std::vector<Coordinate>& coords, double resolution ) const
  {
  coords.clear();
  for( size_t i = 0; i < m_segments.size(); ++i )
    {
    m_segments[i]->discretize( coords, resolution );
    }
  }


std::ostream& CurvedPolygon::print( std::ostream& stream )
  {
  return ( stream << "TODO" << std::endl );
  }
