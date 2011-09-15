#include "latitude.h"

Latitude::Latitude() : LatLon()
{}

Latitude::Latitude(double degrees) : LatLon(degrees)
{}

Latitude::Latitude(int degrees, int minutes, int seconds, char direction)
  : LatLon(degrees, minutes, seconds, direction)
{}

Latitude::Latitude(int degrees, double minutes, char direction)
  : LatLon(degrees, minutes, direction)
{}
