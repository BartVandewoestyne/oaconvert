#include <iostream>
#include "coordinate.h"
#include "latitude.h"
#include "longitude.h"

Coordinate::Coordinate()
{/* Body intentionally empty. */}

Coordinate::Coordinate(Latitude lat, Longitude lon)
{
  this->lat = lat;
  this->lon = lon;
}

Coordinate::Coordinate(double degrees_lat, double degrees_lon)
{
  lat = Latitude(degrees_lat);
  lon = Longitude(degrees_lon);
}

Latitude Coordinate::getLatitude()
{
  return lat;
}

void Coordinate::setLatitude(Latitude lat)
{
  this->lat = lat;
}

Longitude Coordinate::getLongitude()
{
  return lon;
}

void Coordinate::setLongitude(Longitude lon)
{
  this->lon = lon;
}

bool Coordinate::operator ==(const Coordinate& other) const
{
  return ( (lat == other.lat) && (lon == other.lon) );
}

ostream& operator <<(ostream& outputStream, const Coordinate& c)
{
  outputStream << "Coordinate: (";
  outputStream << c.lat;
  outputStream << ", ";
  outputStream << c.lon;
  outputStream << ")";

  return outputStream;
}
