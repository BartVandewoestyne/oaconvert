#ifndef REGION_H
#define REGION_H

#include <ostream>

class Region
  {
public:
  virtual ~Region() {};

  // TODO: define the interface
  virtual std::ostream& print( std::ostream &stream ) = 0;
  };

#endif /* end of include guard: REGION_H */
