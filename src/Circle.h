#ifndef CIRCLE_H 
#define CIRCLE_H 

#include "Coordinate.h"
#include "Region.h"

class Circle : public Region 
  {
  private:
    /* Radius in Nautical Miles */
    Coordinate center;
    double radius;

  public:

//    Circle();

    //! Create a circle around given coordinate and given radius
    //! \param[in] center Center point of the circle.
    //! \param[in] radius Radius in nautical miles
    Circle(const Coordinate& center, double radius);

    

    const Coordinate& getCenter() const;

    //! 
    double getRadiusNM() const;
    double getRadiusM() const;

//    Polygon toPolygon(int nbPoints) const;

    //////////////////////////////////////////////////
    // Interface Region
    virtual std::ostream& print( std::ostream &stream );


    friend std::ostream& operator <<(std::ostream& outputStream, const Circle& c);
  };

#endif /* CIRCLE_H */
