#include "latitude.h"

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
