#include "longitude.h"

Longitude::Longitude() : LatLon()
{
}

Longitude::Longitude(double degrees) : LatLon(degrees)
{
}

Longitude::Longitude(int degrees, int minutes, int seconds, char direction)
  : LatLon(degrees, minutes, seconds, direction)
{
}
