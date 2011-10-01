#include "CurvedPolygon.h"

#include "Arc.h"
#include "Coordinate.h"
#include "LinearSegment.h"

//////////////////////////////////////////////////////////////////////////////////////////

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

std::ostream& CurvedPolygon::print( std::ostream &stream )
  {
  return ( stream << "TODO" << std::endl );
  }

