#ifndef LINEARSEGMENT_H
#define LINEARSEGMENT_H

#include "Coordinate.h"
#include "Segment.h"

class LinearSegment : public Segment
  {
public:
  LinearSegment( const Coordinate& point );
  virtual ~LinearSegment() {};


private:
  Coordinate m_coordinate;
  };

#endif /* end of include guard: LINEARSEGMENT_H */
