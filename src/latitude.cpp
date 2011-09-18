#include "latitude.h"

#include "constants.h"

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

Latitude::Latitude(int degrees, int minutes, int seconds, char direction)
  : LatLon(degrees, minutes, seconds, direction)
{}

Latitude::Latitude(int degrees, double minutes, char direction)
  : LatLon(degrees, minutes, direction)
{}

/**
 * Return the value for an arcdegree of north-south latitude difference.
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: get rid of pi's definition here.
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
