#ifndef ARC_H 
#define ARC_H 

#include "Coordinate.h"
#include "Segment.h"

class Arc : public Segment 
  {

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

    virtual ~Arc() {};

    /* Create an arc around a given coordinate, with radius in nautical miles */
    Arc(const Coordinate& center, double radius, double angleStart, double angleEnd, char direction);

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

    friend std::ostream& operator <<(std::ostream& outputStream, const Arc& c);

    //////////////////////////////////////////////////
    // Interface Segment

    //! @copydoc Segment::discretize
    virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const;

  };

#endif /* ARC_H */
