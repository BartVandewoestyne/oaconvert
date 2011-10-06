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

//////////////////////////////////////////////////////////////////////////////////////////
// Implementation Circle
//////////////////////////////////////////////////////////////////////////////////////////

Circle::Circle(const Coordinate& center, double radius)
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

const Coordinate& Circle::getCenter() const
  {
  return center;
  }

void Circle::write( std::ostream& stream, const OutputState* outputstate ) const
  {
  outputstate->write( stream, this );
  }

void Circle::discretize( std::vector<Coordinate>& coords, double resolution ) const
  {
  size_t nbPoints = (size_t) ( 2 * pi * radius / resolution );
  std::cout << "Circle -- nbPoints: " << nbPoints << std::endl;

  coords.clear();
  coords.reserve(nbPoints);

  double deg_lat, deg_lon;
  double angle;

  Latitude lat = getCenter().getLatitude();
  Longitude lon = getCenter().getLongitude();

  // Compute arcdegree of latitude respectively longitude difference of the center.
  double arcdegree_lat = lat.getArcDegree();
  double arcdegree_lon = lon.getArcDegree(lat);

  for (size_t i = 0; i < nbPoints; ++i)
    {
    angle = i*360.0/nbPoints;

    deg_lon = lon.getAngle() + getRadiusM()*cos(pi*angle/180.0)/arcdegree_lon;
    deg_lat = lat.getAngle() + getRadiusM()*sin(pi*angle/180.0)/arcdegree_lat;
    coords.push_back( Coordinate( deg_lat, deg_lon ) );
    }
  }

std::ostream& Circle::print( std::ostream &stream )
  {
  return ( stream << *this );
  }

///*
// * See http://en.wikipedia.org/wiki/Latitude#Degree_length
// *
// * TODO: check if these calculatiosn (based on the oa2gm source code) are
// *       correct.  I guess not, because they both use 6371e3 for computing
// *       new latitudinal and longitudinal points.  This is not 100% correct.
// *       We should probably follow WGS84 or IERS 2003 ellipsoids.
// */
//Polygon Circle::toPolygon(int nbPoints) const
//{
//
//  double deg_lat, deg_lon;
//  double angle;
//  Polygon p;
//
//  Latitude lat = getCenter().getLatitude();
//  Longitude lon = getCenter().getLongitude();
//
//  // Compute arcdegree of latitude respectively longitude difference.
//  // Note here that we assume latitudinal and longitudinal radius of the
//  // earth to be the same.  It would be more precise to assume different
//  // values.  See M and N-values at
//  //
//  //   http://en.wikipedia.org/wiki/Latitude#Degree_length
//  //
//  double phi = pi*lat.getAngle()/180.0;
//  double arcdegree_lat = pi*lat.getM()/180;
//  double arcdegree_lon = pi*cos(phi)*lon.getN()/180;
//
//  for (int i = 0; i < nbPoints; ++i)
//  {
//    angle = i*360.0/nbPoints;
//
//    deg_lon = lon.getAngle() + getRadiusM()*cos(pi*angle/180)/arcdegree_lon;
//    deg_lat = lat.getAngle() + getRadiusM()*sin(pi*angle/180)/arcdegree_lat;
//    Coordinate c(deg_lat, deg_lon);
//    p.add(c);
//  }
//
//  return p;
//
//}

ostream& operator <<(ostream& outputStream, const Circle& c)
  {
  outputStream << "Circle:" << endl;
  outputStream << "  " << c.center << endl;
  outputStream << "  Radius in NM: " << c.radius;
  return outputStream;
  }
