#include "circle.h"

#include <cmath>

#include "constants.h"

using namespace std;
using Constants::pi;

Circle::Circle()
{
  //cout << "Circle()" << endl;
  setRadiusNM(-1);
}

Circle::Circle(Coordinate center, double radius)
{
  setCenter(center);
  setRadiusNM(radius);
}

bool Circle::isValid() const
{
  if (getRadiusNM() > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Circle::invalidate()
{
  setRadiusNM(-1);
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

/**
 * Set the radius to the specified value in Nautical Miles.
 */
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
 *
 * TODO: check if we should somehow take into account the difference
 *       between airspace coordinate frame and standard coordinate frame.
 */
Polygon Circle::toPolygon(int nbPoints) const
{

  double deg_lat, deg_lon;
  double angle;
  Polygon p;

  Latitude lat = getCenter().getLatitude();
  Longitude lon = getCenter().getLongitude();

  // Compute arcdegree of latitude respectively longitude difference of the center.
  double arcdegree_lat = lat.getArcDegree();
  double arcdegree_lon = lon.getArcDegree(lat);

  for (int i = 0; i < nbPoints; ++i)
  {
    angle = i*360.0/nbPoints;

    deg_lon = lon.getAngle() + getRadiusM()*cos(pi*angle/180)/arcdegree_lon;
    deg_lat = lat.getAngle() + getRadiusM()*sin(pi*angle/180)/arcdegree_lat;
    Coordinate c(deg_lat, deg_lon);
    p.add(c);
  }

  return p;

}

ostream& operator <<(ostream& outputStream, const Circle& c)
{
  outputStream << "Circle:" << endl;
  outputStream << "  " << c.center << endl;
  outputStream << "  Radius in NM: " << c.radius;
  return outputStream;
}
