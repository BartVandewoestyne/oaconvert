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
#include "Constants.h"

#include <cmath>

using namespace std;
using Constants::pi;

Circle::Circle(const Point& center, double radius)
    : m_center( center )
    , m_radiusInNM( radius )
{
}


/**
 * Return the radius in nautical miles.
 */
double Circle::getRadiusInNauticalMiles() const
{
    return m_radiusInNM;
}


/**
 * Return the radius in meter (1 NM = 1852 m).
 */
double Circle::getRadiusInMeter() const
{
    return m_radiusInNM*1852.0;
}


const Point& Circle::getCenter() const
{
    return m_center;
}


/**
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: check if these calculations (based on the oa2gm source code) are
 *       correct.  I guess not, because they both use 6371e3 for computing
 *       new latitude and longitude points.  This is not 100% correct.
 *       We should probably follow WGS84 or IERS 2003 ellipsoids.
 */
void Circle::discretize( std::vector<Coordinate>& coords, double resolution ) const
{
    // Each circle must have *at least* min_nb_points points.  If the specified
    // resolution is not satisfied with min_nb_points, then even more points
    // will be used.  The value of 436 appears to be the smallest value for
    // which we don't have any weird coloring behavior for the top-polygon of
    // small circles.  The smallest circle we have in our OpenAir files is the
    // one from the EHD 61 danger zone in the Netherlands. For this circle with
    // a radius of 300m, it turned out that with 435 points the top-polygon has
    // a weird color, while with 436 and more points it does not...
    const unsigned int min_nb_points = 436;
    unsigned int nbPoints = max( static_cast<unsigned int>(2*pi*m_radiusInNM/resolution), min_nb_points );

    Coordinate centerCoord = m_center.getCoordinate();
    Latitude lat = centerCoord.getLatitude();
    Longitude lon = centerCoord.getLongitude();

    // Compute arcdegree of latitude respectively longitude difference of the center.
    double arcdegree_lat = lat.getArcDegree();
    double arcdegree_lon = lon.getArcDegree(lat);

    coords.clear();
    coords.reserve(nbPoints);

    double deg_lat, deg_lon;
    double angle;
    for (unsigned int i = 0; i < nbPoints; ++i)
    {
        angle = 2*pi*i/nbPoints;

        deg_lon = lon.getAngle() + getRadiusInMeter()*cos(angle)/arcdegree_lon;
        deg_lat = lat.getAngle() + getRadiusInMeter()*sin(angle)/arcdegree_lat;
        coords.push_back( Coordinate( deg_lat, deg_lon ) );
    }
}


ostream& operator<<(ostream& out, const Circle& c)
{
  out << "Circle:" << endl;
  out << "  " << c.getCenter() << endl;
  out << "  Radius in meter         : " << c.getRadiusInMeter();
  out << "  Radius in nautical miles: " << c.getRadiusInNauticalMiles();
	return out;
}
