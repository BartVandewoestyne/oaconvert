#ifndef REGION_H
#define REGION_H

#include <ostream>
#include <vector>

#include "Coordinate.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
//////////////////////////////////////////////////////////////////////////////////////////
class OutputState;

//////////////////////////////////////////////////////////////////////////////////////////
// Interface Region
//////////////////////////////////////////////////////////////////////////////////////////
class Region
  {
  public:
    virtual ~Region() {};

    virtual void write( std::ostream& stream, const OutputState* outputstate ) const = 0;

    virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const = 0;

    virtual std::ostream& print( std::ostream &stream ) = 0;
  };

#endif /* end of include guard: REGION_H */
