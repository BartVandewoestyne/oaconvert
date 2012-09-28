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

#include "Point.h"
#include "OutputState.h"
#include "Coordinate.h"
#include "GeometricShape.h"

class Circle : public GeometricShape
{
private:

    Point m_center;

    /* Radius in Nautical Miles */
    double m_radiusInNM;

public:
    //! Create a circle around given point and given radius
    //! \param[in] center Center point of the circle.
    //! \param[in] radius Radius in nautical miles
    Circle(const Point& center, double radius);

    const Point& getCenter() const;
    double getRadiusInNauticalMiles() const;
    double getRadiusInMeter() const;

    virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const;

};


std::ostream& operator<<(std::ostream& out, const Circle& c);

#endif /* CIRCLE_H */
