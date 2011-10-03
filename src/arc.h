#ifndef ARC_H 
#define ARC_H 

#include "coordinate.h"
#include "polygon.h"

class Arc {

  private:
    /* Radius in Nautical Miles */
    double radius;

    /* Arc center */
    Coordinate center;

    /* Start and end angle of the arc. */
    double angleStart, angleEnd;

    /* Direction in which the arc should be drawn:
        '+' clockwise (default)
        '-' counterclockwise */
    char direction;

  public:

    /* Create an (invalid) arc. */
    Arc();

    /* Create an arc around a given coordinate, with radius in nautical miles */
    // Note that for now, we assume angleStart and angleEnd to be integers.  I haven't seen
    // OpenAir files with floating-point values for these values yet...
    Arc(Coordinate center, double radius, double angleStart, double angleEnd, char direction);

    bool isValid() const;
    void invalidate();
    void setRadiusNM(double radius);
    void setCenter(Coordinate c);
    void setDirection(char d);
    char getDirection() const;
    const Coordinate& getCenter() const;
    double getRadiusNM() const;
    double getRadiusM() const;
    void setStartAngle(double angle);
    double getStartAngle() const;
    void setEndAngle(double angle);
    double getEndAngle() const;
    Polygon toPolygon(int nbPoints) const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Arc& c);

};

#endif /* ARC_H */
