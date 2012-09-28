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

#include "Arc.h"

#include <cmath>
#include "Constants.h"

using namespace std;
using Constants::pi;

// TODO: I don't like -1 and -1 as start and end angle as these are plausible
// values... how to solve this?
Arc::Arc()
    : m_radiusInNauticalMiles(-1.0)
    , m_center()
    , m_start_angle(-1.0)
    , m_end_angle(-1.0)
    , m_clockdirection('+')
{
}

Arc::Arc(const Point& center, double radius, double angleStart, double angleEnd, char direction)
    : m_radiusInNauticalMiles(radius)
    , m_center(center)
    , m_start_angle(angleStart)
    , m_end_angle(angleEnd)
    , m_clockdirection(direction)
{
}


/**
 * Return the radius in nautical miles.
 */
double Arc::getRadiusInNauticalMiles() const
{
    return m_radiusInNauticalMiles;
}

/**
 * Return the radius in metres (1 NM = 1852 m).
 */
double Arc::getRadiusInMeters() const
{
    return m_radiusInNauticalMiles*1852.0;
}


char Arc::getAngleDirection() const
{
    return m_clockdirection;
}


/**
  * Return the start angle in airspace coordinate frame conventions.
  */
double Arc::getStartAngle() const
{
    return m_start_angle;
}

/**
  * Return the end angle in airspace coordinate frame conventions.
  */
double Arc::getEndAngle() const
{
    return m_end_angle;
}

const Point& Arc::getCenter() const
{
    return m_center;
}

/**
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: check if these calculations (based on the oa2gm source code) are
 *       correct.  I guess not, because they both use 6371e3 for computing
 *       new latitudinal and longitudinal points.  This is not 100% correct.
 *       We should probably follow WGS84 or IERS 2003 ellipsoids.
 */
void Arc::discretize( std::vector<Coordinate>& coords, double resolution ) const
{
    double deg_lat, deg_lon;
    double angle;

    Coordinate centerCoord = m_center.getCoordinate();
    Latitude lat = centerCoord.getLatitude();
    Longitude lon = centerCoord.getLongitude();

    // Reduce angles so that they are in [0, 360[.
    // TODO: this worked for integer angles, but not for floating point values...
    // So for now, we assume that all start and end angles are in [0, 360[.
    //double startAngle = getStartAngle() % 360;
    //double endAngle = getEndAngle() % 360;
    double startAngle = getStartAngle();
    double endAngle = getEndAngle();

    // Make sure that start angle is smaller than end angle.
    if (startAngle > endAngle)
    {
        startAngle = startAngle - 360;
    }

    double interval;
    if (getAngleDirection() == '-')
    {
        interval = -( 360-(endAngle-startAngle) );
    }
    else // Default (or non specified) is positive direction.
    {
        interval = endAngle - startAngle;
    }

    // Compute arcdegree of latitude respectively longitude difference of the center.
    double arcdegree_lat = lat.getArcDegree();
    double arcdegree_lon = lon.getArcDegree(lat);

    // Compute the number of points of the discretization.
    //size_t nbPoints = (size_t) ( 2 * pi * ( interval / 360.0 ) * radiusNM / resolution );
    int nbPoints = static_cast<int> ( abs( 2 * pi * ( interval / 360.0 ) * m_radiusInNauticalMiles / resolution ) );

    // Generate all points of the arc.
    for (int i = 0; i < nbPoints; ++i)
    {
        // 'Normal' geometric angles are COUNTERCLOCKWISE as follows:
        //
        //   0 degrees = 360 degrees = East
        //   90 degrees = North
        //   180 degrees = West
        //   270 degrees = South
        //
        // The convention in the DA-records is CLOCKWISE and as follows:
        //
        //   0 degrees = 360 degrees = North
        //   90 degrees = East
        //   180 degrees = South
        //   270 degrees = West
        //
        // So we have to transform the coordinates from the DA-records
        // to 'normal' geometric angles.  We do this by first mirroring along
        // the vertical axis and then rotating -90 degrees.

        // Generate arc-points in airspace (DA-record) coordinate frame, centered
        // around the origin.
        // TODO: note that delta_lon uses arcdegree_lat and delta_lat uses arcdegree_lon... this
        //       is strange, but it seems to work... check out why!/
        angle = startAngle + (interval*i)/(nbPoints-1);
        double delta_lon = getRadiusInMeters()*cos(pi*angle/180.0)/arcdegree_lat; // TODO: why arcdegree_lat here???
        double delta_lat = getRadiusInMeters()*sin(pi*angle/180.0)/arcdegree_lon; // TODO: why arcdegree_lon here???

        // Transform points to standard coordinate frame:
        //
        //   Step 1: mirror around Y-axis
        //           -> transformation matrix = [-1 0; 0 1]
        //
        //   Step 2: rotate -90 degrees
        //           -> transformation matrix = [0 1; -1 0]
        //
        // The total transformation matrix is:
        //
        //    [0 1; -1 0]*[-1 0; 0 1] = [0 1; 1 0]
        //
        // so what we actually do is simply swap x and y coordinates of the arc.
        double temp = delta_lon;
        delta_lon = delta_lat;
        delta_lat = temp;

        // Now add the coordinates of the generated circle to the location of the centerpoint
        // (= translate the generated circle from the origin to the correct location).
        deg_lon = lon.getAngle() + delta_lon;
        deg_lat = lat.getAngle() + delta_lat;

        coords.push_back( Coordinate(deg_lat, deg_lon) );
    }
}


ostream& operator<<(ostream& out, const Arc& arc)
{
    out << "Arc of "
        << arc.getRadiusInNauticalMiles()
        << " NM in "
        << arc.getAngleDirection()
        << " direction from "
        << arc.getStartAngle()
        << " to "
        << arc.getEndAngle()
        << " degrees and centered at " << arc.getCenter();
    return out;
}
