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

#include <string>
#include "LatLon.h"
#include "Constants.h"

using namespace std;
using Constants::pi;

LatLon::LatLon()
    : angle(-1)
{}


LatLon::LatLon(double angle)
    : angle(angle)
{
    // TODO:
    // Since for latitudes we have that -90 <= angle <= 90 and for longitudes
    // we have that -180 <= angle <= 180, we could check here if
    //
    //   -180 <= angle <= 180
    //
    // and throw an exception if this condition is not satisfied?
}


LatLon::LatLon(int degrees, int minutes, double seconds)
    : angle(degrees + minutes/60.0 + seconds/3600.0)
{}

LatLon::LatLon(int degrees, double minutes)
    : angle(degrees + minutes/60.0)
{}

LatLon::~LatLon() {}

/**
 * Return the complete angle as a positive or negative floating point number.
 */
double LatLon::getAngle() const
{
    return angle;
}


/**
 * Return the (positive) integer value for the degrees ( the DD in DD:MM:SS, which is
 * equal to abs( getAngle() minus its fractional part) ).
 */
int LatLon::getDegrees() const
{
    return abs( (int) angle );
}

/**
 * Return the integer value for the minutes (the MM in DD:MM:SS).
 */
int LatLon::getMinutes() const
{
    return (int) ((getAngle()-getDegrees())*60.0);
}

/**
 * Return the floating point value for the seconds (the SS in DD:MM:SS).
 */
double LatLon::getSeconds() const
{
    return (getAngle()-getDegrees()-getMinutes()/60.0)*3600;
}

/**
 * Return the angle in radians.
 */
const double LatLon::toRadians() const
{
    return pi*angle/180.0;
}

bool LatLon::operator ==(const LatLon& other) const
{
    // TODO: we are comparing floating point values here... we should
    //       allow some tolerance...
    return ( (angle == other.angle) );
}

ostream& operator <<(ostream& outputStream, const LatLon& l)
{
    outputStream << l.angle;

    return outputStream;
}
