#include "circle.h"

#include <cmath>

#include "constants.h"

using namespace std;
using Constants::pi;

Circle::Circle()
{}

Circle::Circle(Coordinate center, double radius)
{
  setCenter(center);
  setRadiusNM(radius);
}

/*
 * Return the radius in nautical miles.
 */
double Circle::getRadiusNM() const
{
  return radius;
}

/*
 * Return the radius in metres.
 */
double Circle::getRadiusM() const
{
  return radius*1852.0;
}

void Circle::setRadiusNM(double r)
{
  radius = r;
}

void Circle::setCenter(Coordinate c)
{
  center = c;
}

const Coordinate& Circle::getCenter() const
{
  return center;
}

/*
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: check if these calculatiosn (based on the oa2gm source code) are
 *       correct.  I guess not, because they both use 6371e3 for computing
 *       new latitudinal and longitudinal points.  This is not 100% correct.
 *       We should probably follow WGS84 or IERS 2003 ellipsoids.
 */
void Circle::toPolish( ostream& outputStream ) const
{
  // Resolution of the circle.  Currently, we use the same value as the
  // oa2gm program, but in the future we might make this configurable via
  // a configuration file.
  int steps = 100;

  const double pi = 3.14159265;
  double deg_lat, deg_lon;
  double angle;

  Latitude lat = getCenter().getLatitude();
  Longitude lon = getCenter().getLongitude();

  // Compute arcdegree of latitude respectively longitude difference.
  // Note here that we assume latitudinal and longitudinal radius of the
  // earth to be the same.  It would be more precise to assume different
  // values.  See M and N-values at
  //
  //   http://en.wikipedia.org/wiki/Latitude#Degree_length
  //
  double phi = pi*lat.getAngle()/180.0;
  double arcdegree_lat = pi*lat.getM()/180;
  double arcdegree_lon = pi*cos(phi)*lon.getN()/180;

  for (int i = 0; i < steps; ++i)
  {
    angle = i*360.0/steps;

    deg_lon = lon.getAngle() + getRadiusM()*cos(pi*angle/180)/arcdegree_lon;
    deg_lat = lat.getAngle() + getRadiusM()*sin(pi*angle/180)/arcdegree_lat;
    Coordinate c(deg_lat, deg_lon);
    outputStream << c << endl;
  }

}

ostream& operator <<(ostream& outputStream, const Circle& c)
{
  outputStream << "Circle:" << endl;
  outputStream << "  " << c.center << endl;
  outputStream << "  Radius in NM: " << c.radius;
  return outputStream;
}
