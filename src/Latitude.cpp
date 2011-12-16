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

Latitude::Latitude() : LatLon()
{}

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

Latitude::Latitude(int degrees, int minutes, int seconds, char direction)
    : LatLon(abs(degrees) + abs(minutes)/60.0 + abs(seconds)/3600.0)
{
  applyDirection(direction);
}

/**
 * Return the value for an arcdegree of north-south latitude difference.
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 */
double Latitude::getArcDegree()
{
    return pi*getM()/180.0;
}

/**
 * Return the meridional radius of curvature.
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 * TODO: use correct formula instead of 6371e3.
 */
double Latitude::getM()
{
    // Th value 3671e3 is taken from the oa2gm program.  Note that
    // http://en.wikipedia.org/wiki/Latitude#Degree_length mentions
    // a value of 6378137m for the equatorial radius... maybe we should use
    // that more precise value?
    // According to http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth
    // the value 6371000 is just the mean radius...

    // Currently, we use an approximation of 6371e3, but in reality this value
    // depends on the angle.
    return 6371e3;
}

const char Latitude::getDirection() const {

    if (getAngle() < 0)
    {
        return 'S';
    }
    else
    {
        return 'N';
    }

}

const void Latitude::applyDirection(const char direction) {

  // just to be on the safe side, make the angle positive...
  angle = abs(angle);

  // ... and invert its sign when necessary.
  if ( direction == 's' || direction == 'S' ) {
    angle = -angle;
  }

}
