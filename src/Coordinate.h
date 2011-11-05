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

#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <stdlib.h>
#include <string>

#include "Latitude.h"
#include "Longitude.h"

class Coordinate
{

private:
    Latitude lat;
    Longitude lon;

public:
    Coordinate();
    Coordinate(std::string);
    Coordinate(const Latitude& lat, const Longitude& lon);
    Coordinate(double degrees_lat, double degrees_lon);

    const Latitude& getLatitude() const;
    const Longitude& getLongitude() const;

    void setLatitude(const Latitude& lat);
    void setLongitude(const Longitude& lon);

    void toPolish(std::ostream& outputStream) const;
    double getDistance(const Coordinate& c) const;

    bool operator ==(const Coordinate& other) const;
    friend std::ostream& operator <<(std::ostream& outputStream, const Coordinate& c);

};

#endif /* COORDINATE_H */
