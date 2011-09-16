#ifndef CIRCLE_H 
#define CIRCLE_H 

#include "coordinate.h"

class Circle {

  private:
    /* Radius in Nautical Miles */
    double radius;
    Coordinate center;

  public:
    Circle();
    /* Create a circle around given coordinate, with radius in nautical miles */
    Circle(Coordinate c1, double radius);
    void setRadiusNM(double radius);
    void setCenter(Coordinate c);
    Coordinate& getCenter();
    double getRadiusNM();
    double getRadiusM();
    void toPolish();
    friend ostream& operator <<(ostream& outputStream, const Circle& c);

};

#endif /* CIRCLE_H */
