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

#include "Circle.h"

#include <cmath>

#include "Constants.h"
#include "OutputState.h"

using namespace std;
using Constants::pi;

Circle::Circle(const Point& center, double radius)
    : center( center )
    , radius( radius )
{
}

/**
 * Return the radius in nautical miles.
 */
double Circle::getRadiusNM() const
{
    return radius;
}

/**
 * Return the radius in metres (1 NM = 1852 m).
 */
double Circle::getRadiusM() const
{
    return radius*1852.0;
}

const Point& Circle::getCenter() const
{
    return center;
}

void Circle::write( std::ostream& stream, const OutputState* outputstate ) const
{
    outputstate->write( stream, this );
}

/**
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: check if these calculatiosn (based on the oa2gm source code) are
 *       correct.  I guess not, because they both use 6371e3 for computing
 *       new latitudinal and longitudinal points.  This is not 100% correct.
 *       We should probably follow WGS84 or IERS 2003 ellipsoids.
 */
void Circle::discretize( std::vector<Coordinate>& coords, double resolution ) const
{

    // Each circle must have *at least* 360 points (or more if the specified resolution is
    // not satisfied when taking 360 points).
    const int min_nb_points = 360;
    int nbPoints = max((int)(2*pi*radius/resolution), min_nb_points);

    coords.clear();
    coords.reserve(nbPoints);

    double deg_lat, deg_lon;
    double angle;

    Coordinate centerCoord = center.getCoordinate();
    Latitude lat = centerCoord.getLatitude();
    Longitude lon = centerCoord.getLongitude();

    // Compute arcdegree of latitude respectively longitude difference of the center.
    double arcdegree_lat = lat.getArcDegree();
    double arcdegree_lon = lon.getArcDegree(lat);

    for (int i = 0; i < nbPoints; ++i)
    {
        angle = 2*pi*i/nbPoints;

        deg_lon = lon.getAngle() + getRadiusM()*cos(angle)/arcdegree_lon;
        deg_lat = lat.getAngle() + getRadiusM()*sin(angle)/arcdegree_lat;
        coords.push_back( Coordinate( deg_lat, deg_lon ) );
    }
}


std::ostream& Circle::print( std::ostream &stream )
{
    return ( stream << *this );
}


ostream& operator <<(ostream& outputStream, const Circle& c)
{
    outputStream << "Circle:" << endl;
    outputStream << "  " << c.center << endl;
    outputStream << "  Radius in NM: " << c.radius;
    return outputStream;
}
