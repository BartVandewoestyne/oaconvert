#ifndef POLYGON_H
#define POLYGON_H 

#include <stdlib.h>
#include <vector>
#include "point.h"

class Polygon {

  private:
    std::vector<Coordinate> coords;

  public:
    Polygon();
    void add(Coordinate c);
    void toPolish();
    void clear();
    int getNbPoints() const;
    friend ostream& operator <<(ostream& outputStream, const Polygon& c);

};

#endif /* POLYGON_H */
