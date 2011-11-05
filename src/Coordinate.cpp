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

#include <iostream>
#include <math.h>

#include "Coordinate.h"
#include "Latitude.h"
#include "Longitude.h"

using namespace std;

Coordinate::Coordinate()
{
    /* Body intentionally empty. */
}

Coordinate::Coordinate(const Latitude& lat, const Longitude& lon)
    : lat( lat )
    , lon( lon )
{
}

Coordinate::Coordinate(double degrees_lat, double degrees_lon)
    : lat( degrees_lat )
    , lon( degrees_lon )
{
}

const Latitude& Coordinate::getLatitude() const
{
    return lat;
}

const Longitude& Coordinate::getLongitude() const
{
    return lon;
}

void Coordinate::setLatitude(const Latitude& lat)
{
    this->lat = lat;
}

void Coordinate::setLongitude(const Longitude& lon)
{
    this->lon = lon;
}

bool Coordinate::operator ==(const Coordinate& other) const
{
    return ( (lat == other.lat) && (lon == other.lon) );
}

void Coordinate::toPolish(ostream& outputStream) const
{
    outputStream << "(" << lat.getAngle() << "," << lon.getAngle() << ")" << endl;
}

/**
 * Compute the distance from this coordinate to another coordinate
 * using the 'haversine' formula.  This formula assumes the earth is a
 * spheroid.  See http://www.movable-type.co.uk/scripts/latlong.html
 *
 * TODO: Check if we can do this more precise.  Currently, the precision of this
 *       distance calculation seems to be 47 metres (see test/CoordinateTest.cpp).
 *
 * TODO: There exist formulae for computing the distance on a WGS84 earth ellipsoid.  See for
 *       example `Direct and inverse solutions of geodesics on the ellipsoid with application
 *       of nested equations', Vincenty, Thaddeus, 1975.
 *
 *         http://www.movable-type.co.uk/scripts/latlong-vincenty.html
 *         http://www.mathworks.com/matlabcentral/fileexchange/5379
 *
 *       This is the method that the script at http://www.penguin.cz/~ondrap/paragliding.php
 *       uses.
 */
double Coordinate::getDistance(const Coordinate& other) const
{

    double lat1, lat2;
    double lon1, lon2;
    double dLat, dLon;

    // Earth radius, assuming the earth is a spheroid.
    // TODO: Find more precise value???
    const double R = 6371e3;

    // Convert latitudes and longitudes to radians.
    lat1 = getLatitude().toRadians();
    lon1 = getLongitude().toRadians();
    lat2 = other.getLatitude().toRadians();
    lon2 = other.getLongitude().toRadians();

    // Compute the differences in radians.
    dLat = lat2 - lat1;
    dLon = lon2 - lon1;

    // Square of half the chord length between the points.
    double a = sin(dLat/2)*sin(dLat/2)
               + sin(dLon/2)*sin(dLon/2)*cos(lat1)*cos(lat2);

    // Angular distance in radians
    double c = 2*atan2(sqrt(a), sqrt(1-a));

    double d = R*c;

    return d;

}

ostream& operator <<(ostream& outputStream, const Coordinate& c)
{
    outputStream << "Coordinate (";
    outputStream << c.lat;
    outputStream << ", ";
    outputStream << c.lon;
    outputStream << ") = (";
    outputStream << c.getLatitude().getDegrees() << ":";
    outputStream << c.getLatitude().getMinutes() << ":";
    outputStream << c.getLatitude().getSeconds() << " ";
    outputStream << c.getLatitude().getDirection() << ", ";
    outputStream << c.getLongitude().getDegrees() << ":";
    outputStream << c.getLongitude().getMinutes() << ":";
    outputStream << c.getLongitude().getSeconds() << " ";
    outputStream << c.getLongitude().getDirection() << ")";

    return outputStream;
}
