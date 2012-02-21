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

#include "Longitude.h"

#include <cmath>
#include <iostream>

#include "Constants.h"

using Constants::pi;
using namespace std;

Longitude::Longitude() : LatLon()
{}

Longitude::Longitude(double angle) : LatLon(angle)
{}

Longitude::Longitude(double degrees, char direction)
    : LatLon(abs(degrees))
{
    applyDirection(direction);
}

Longitude::Longitude(int degrees, double minutes, char direction)
    : LatLon(abs(degrees) + abs(minutes)/60.0)
{
    applyDirection(direction);
}

Longitude::Longitude(int degrees, int minutes, int seconds, char direction)
    : LatLon(abs(degrees) + abs(minutes)/60.0 + abs(seconds)/3600.0)
{
    applyDirection(direction);
}

/**
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: check the theory if we really nead lat.getAngle() or lon.getAngle().
 */
double Longitude::getArcDegree(const Latitude& lat)
{
    return pi*cos(pi*lat.getAngle()/180.0)*getN()/180.0;
}

/**
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 * TODO: find exact formula for N, the normal radius of curvature.
 */
double Longitude::getN()
{
    // Th value 3671e3 is taken from the oa2gm program.  Note that
    // http://en.wikipedia.org/wiki/Latitude#Degree_length mentions
    // a value of 6378137m for the equatorial radius... maybe we should use
    // that more precise value?
    // According to http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth
    // the value 6371000 is just the mean radius...
    return 6371e3;
}

char Longitude::getDirection() const {

    if (getAngle() < 0)
    {
        return 'W';
    }
    else
    {
        return 'E';
    }

}

void Longitude::applyDirection(const char direction) {

  // just to be on the safe side, make the angle positive...
  angle = abs(angle);

  // ... and invert its sign when necessary.
  if ( direction == 'w' || direction == 'W' ) {
    angle = -angle;
  }

}
