#include "longitude.h"

#include <cmath>

#include "constants.h"

using Constants::pi;

Longitude::Longitude() : LatLon()
{}

Longitude::Longitude(double degrees) : LatLon(degrees)
{
  if (getAngle() < 0)
  {
    setDirection('W');
  }
  else
  {
    setDirection('E');
  }
}

Longitude::Longitude(int degrees, int minutes, int seconds, char direction)
  : LatLon(degrees, minutes, seconds, direction)
{}

Longitude::Longitude(int degrees, double minutes, char direction)
  : LatLon(degrees, minutes, direction)
{}

/**
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 */
double Longitude::getArcDegree()
{
  return pi*cos(pi*getAngle()/180)*getN()/180.0;
}

/**
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 * TODO: find exact formula for N, the normal radius of curvature.
 */
double Longitude::getN()
{
  // Th value 3671e3 is taken from the oa2gm program.  Note that
  // http://en.wikipedia.org/wiki/Latitude#Degree_length mentions
  // a value of 6378137m for the equatorial radius... maybe we should use
  // that more precise value?
  // According to http://solarsystem.nasa.gov/planets/profile.cfm?Object=Earth
  // the value 6371000 is just the mean radius...
  return 6371e3;
}
