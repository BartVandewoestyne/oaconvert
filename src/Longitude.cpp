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

Longitude::Longitude(int degrees, int minutes, double seconds, char direction)
    : LatLon(abs(degrees) + abs(minutes)/60.0 + abs(seconds)/3600.0)
{
    applyDirection(direction);
}

/**
 * Return the arcdegree length in case of a spherical model of the earth.
 *
 * See http://en.wikipedia.org/wiki/Longitude#Length_of_a_degree_of_longitude
 *
 * TODO: Return the same, but for an elliptical model of the earth.
 */
double Longitude::getArcDegree(const Latitude& lat)
{
    return pi*cos(pi*lat.getAngle()/180.0)*getN()/180.0;
}

/**
 * Return the normal radius of curvature for a spherical model of the earth.
 *
 * TODO: implement the normal radius of curvature for an elliptical model of the earth.
 */
double Longitude::getN()
{
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
