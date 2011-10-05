/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.
  
  This file is part of oaconvert.
  
  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    //! Create a circle around given coordinate and given radius
    //! \param[in] center Center point of the circle.
    //! \param[in] radius Radius in nautical miles
    Circle(const Coordinate& center, double radius);

    const Coordinate& getCenter() const;

    double getRadiusNM() const;

    double getRadiusM() const;

//    Polygon toPolygon(int nbPoints) const;

    //////////////////////////////////////////////////
    // Interface Region
    //! @copydoc Region::write
    virtual void write( std::ostream& stream, const OutputState* outputstate ) const;

    //! @copydoc Region::discretize
    virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const;

    //! @copydoc Region::print
    virtual std::ostream& print( std::ostream &stream );

    friend std::ostream& operator <<( std::ostream& outputStream, const Circle& c );
  };

#endif /* CIRCLE_H */
