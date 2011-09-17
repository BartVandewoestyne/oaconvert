#include "longitude.h"

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
