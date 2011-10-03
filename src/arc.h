#ifndef ARC_H 
#define ARC_H 

#include "coordinate.h"
#include "polygon.h"

class Arc {

  private:

    /* Radius in Nautical Miles. */
    double radiusNM;

    /* Arc center. */
    Coordinate center;

    /* Start and end angle of the arc, following airspace coordinate frame conventions!!! */
    double angleStart, angleEnd;

    /* Direction in which the arc should be drawn:
        '+' clockwise (default)
        '-' counterclockwise */
    char direction;

  public:

    /* Create an (invalid) arc. */
    Arc();

    /* Create an arc around a given coordinate, with radius in nautical miles */
    Arc(Coordinate center, double radiusNM, double angleStart, double angleEnd, char direction);

    double getRadiusNM() const;
    double getRadiusM() const;
    const Coordinate& getCenter() const;
    double getStartAngle() const;
    double getEndAngle() const;
    char getDirection() const;

    void setRadiusNM(double radiusNM);
    void setCenter(Coordinate c);
    void setStartAngle(double angle);
    void setEndAngle(double angle);
    void setDirection(char d);

    bool isValid() const;
    void invalidate();
    Polygon toPolygon(int nbPoints) const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Arc& c);

};

#endif /* ARC_H */
