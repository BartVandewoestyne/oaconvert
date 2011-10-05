#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>

#include "Coordinate.h"


class Segment
  {
public:
  virtual ~Segment() {};

  virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const = 0;

  };


#endif /* end of include guard: SEGMENT_H */
