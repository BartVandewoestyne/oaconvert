#ifndef POINT_H
#define POINT_H 

#include <stdlib.h>
#include "coordinate.h"

class Point {

  private:
    Coordinate coord;

  public:
    Coordinate getCoordinate();

};

#endif /* POINT_H */
