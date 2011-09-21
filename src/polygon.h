#ifndef POLYGON_H
#define POLYGON_H 

#include <stdlib.h>
#include <vector>

#include "coordinate.h"
#include "point.h"

class Polygon {

  private:
    std::vector<Coordinate> coords;

  public:
    Polygon();

    void add(const Coordinate& c);
    void add(const Polygon& p);
    void clear();
    int getNbPoints() const;
    const Coordinate& getCoordinate(int i) const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Polygon& c);

};

#endif /* POLYGON_H */
