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

#ifndef LATITUDE_H
#define LATITUDE_H

#include "LatLon.h"

class Latitude : public LatLon
{

public:

    Latitude(double angle);
    Latitude(double degrees, char direction);
    Latitude(int degrees, double minutes, char direction);
    Latitude(int degrees, int minutes, double seconds, char direction);

    char getDirection() const;

    double getArcDegree();
    double getM();

private:

    void applyDirection(const char direction);

};

#endif /* LATITUDE_H */
