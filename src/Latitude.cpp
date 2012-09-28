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

// TODO: for the constructors that also have a direction as parameter, we should
//       check if the value for degrees (minutes, seconds) is positive.

#include <cmath>
#include "Latitude.h"
#include "Constants.h"

using Constants::pi;
using namespace std;

Latitude::Latitude(double angle) : LatLon(angle)
{}

Latitude::Latitude(double degrees, char direction)
    : LatLon(abs(degrees))
{
  applyDirection(direction);
}

Latitude::Latitude(int degrees, double minutes, char direction)
    : LatLon(abs(degrees) + abs(minutes)/60.0)
{
  applyDirection(direction);
}

Latitude::Latitude(int degrees, int minutes, double seconds, char direction)
    : LatLon(abs(degrees) + abs(minutes)/60.0 + abs(seconds)/3600.0)
{
  applyDirection(direction);
}

/**
 * Return the value for an arcdegree of north-south latitude difference
 * for a spherical model of the earth.
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: implement this function for other models of the earth.
 */
double Latitude::getArcDegree()
{
    return pi*getM()/180.0;
}

/**
 * Return the meridional radius of curvature for a spherical model of the
 * earth.  In case of a spherical model of the earth, the meridional radius
 * of curvature is equal to the mean radius of the earth.
 *
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: implement meridional radius of curvature for other models of the
 *       earth.
 */
double Latitude::getM()
{
    return 6371e3;
}

char Latitude::getDirection() const {

    if (getAngle() < 0)
    {
        return 'S';
    }
    else
    {
        return 'N';
    }

}

void Latitude::applyDirection(const char direction) {

  // just to be on the safe side, make the angle positive...
  angle = abs(angle);

  // ... and invert its sign when necessary.
  if ( direction == 's' || direction == 'S' ) {
    angle = -angle;
  }

}
