#ifndef CIRCLE_H 
#define CIRCLE_H 

#include <Region.h>

#include "coordinate.h"
#include "polygon.h"

class Circle : public Region 
  {
  private:
    /* Radius in Nautical Miles */
    double radius;
    Coordinate center;

  public:

    Circle();

    //! Create a circle around given coordinate and given radius
    //! \param[in] center Center point of the circle.
    //! \param[in] radius Radius in nautical miles
    Circle(const Coordinate& center, double radius);

    const Coordinate& getCenter() const;

    //! 
    double getRadiusNM() const;
    double getRadiusM() const;

//    Polygon toPolygon(int nbPoints) const;

    friend std::ostream& operator <<(std::ostream& outputStream, const Circle& c);
  };

#endif /* CIRCLE_H */
