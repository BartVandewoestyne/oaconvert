#include "LinearSegment.h"

LinearSegment::LinearSegment( const Coordinate& point )
: m_coordinate( point )
  {
  }

void LinearSegment::discretize( std::vector<Coordinate>& coords, double resolution ) const
  {
  coords.push_back( m_coordinate );
  }

