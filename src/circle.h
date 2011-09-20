#ifndef CIRCLE_H 
#define CIRCLE_H 

#include "coordinate.h"
#include "polygon.h"

class Circle {

  private:
    /* Radius in Nautical Miles */
    double radius;
    Coordinate center;

  public:
    Circle();
    /* Create a circle around given coordinate, with radius in nautical miles */
    Circle(Coordinate center, double radius);

    bool isValid() const;
    void invalidate();
    void setRadiusNM(double radius);
    void setCenter(Coordinate c);
    const Coordinate& getCenter() const;
    double getRadiusNM() const;
    double getRadiusM() const;
    Polygon toPolygon(int nbPoints) const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Circle& c);

};

#endif /* CIRCLE_H */
