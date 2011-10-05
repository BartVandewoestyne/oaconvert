#include "LinearSegment.h"

LinearSegment::LinearSegment( const Coordinate& point )
: m_coordinate( point )
  {
  }

void LinearSegment::discretize( std::vector<Coordinate>& coords, double resolution ) const
  {
  // TODO: resolution is not used here???  This feels strange... we can do probably do this in a cleaner way!
  coords.push_back( m_coordinate );
  }

