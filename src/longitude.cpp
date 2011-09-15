#include "longitude.h"

Longitude::Longitude() : LatLon()
{}

Longitude::Longitude(double degrees) : LatLon(degrees)
{}

Longitude::Longitude(int degrees, int minutes, int seconds, char direction)
  : LatLon(degrees, minutes, seconds, direction)
{}

Longitude::Longitude(int degrees, double minutes, char direction)
  : LatLon(degrees, minutes, direction)
{}
