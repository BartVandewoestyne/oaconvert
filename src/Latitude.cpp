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

#include "Latitude.h"

#include "Constants.h"

using Constants::pi;

Latitude::Latitude() : LatLon()
{}

Latitude::Latitude(double degrees) : LatLon(degrees)
{
    if (getAngle() < 0)
    {
        setDirection('S');
    }
    else
    {
        setDirection('N');
    }
}

Latitude::Latitude(double degrees, char direction)
    : LatLon(degrees, direction)
{}

Latitude::Latitude(int degrees, int minutes, int seconds, char direction)
    : LatLon(degrees, minutes, seconds, direction)
{}

Latitude::Latitude(int degrees, double minutes, char direction)
    : LatLon(degrees, minutes, direction)
{}

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
