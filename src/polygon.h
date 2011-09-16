#ifndef POLYGON_H
#define POLYGON_H 

#include <stdlib.h>
#include <vector>
#include "point.h"

class Polygon {

  private:
    std::vector<Coordinate> coords;

  public:
    void add(Coordinate c);
    void draw();
    void clear();
    int getNbPoints();
    friend ostream& operator <<(ostream& outputStream, const Polygon& c);

};

#endif /* POLYGON_H */
