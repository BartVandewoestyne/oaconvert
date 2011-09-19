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

    void add(const Coordinate &c);
    void clear();
    int getNbPoints() const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Polygon& c);

};

#endif /* POLYGON_H */
