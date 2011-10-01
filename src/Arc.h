#ifndef ARC_H 
#define ARC_H 

#include "Coordinate.h"
#include "Segment.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Class Arc
//////////////////////////////////////////////////////////////////////////////////////////

class Arc : public Segment 
  {

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

    virtual ~Arc() {};

    /* Create an arc around a given coordinate, with radius in nautical miles */
    // Note that for now, we assume angleStart and angleEnd to be integers.  I haven't seen
    // OpenAir files with floating-point values for these values yet...
    Arc(Coordinate center, double radius, int angleStart, int angleEnd, char direction);

    bool isValid() const;
    void invalidate();

    void setRadiusNM(double radius);
    double getRadiusNM() const;
    double getRadiusM() const;

    void setCenter(Coordinate c);
    const Coordinate& getCenter() const;

    void setDirection(char d);
    char getDirection() const;

    void setStartAngle(int angle);
    int getStartAngle() const;

    void setEndAngle(int angle);
    int getEndAngle() const;

//    Polygon toPolygon(int nbPoints) const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Arc& c);

  };

#endif /* ARC_H */
