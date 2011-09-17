// vim: expandtab 
#include <iostream>

#include "coordinate.h"
#include "latitude.h"
#include "longitude.h"

using namespace std;

Coordinate::Coordinate()
{/* Body intentionally empty. */}

Coordinate::Coordinate(const Latitude& lat, const Longitude& lon)
: lat( lat ) // use initializer list! If not, first the default
                   // constructor is called, then, in the implementation of the
                   // constructor, the assignments operator is called. This is
                   // double the amount of work that should be necessary ;)
, lon( lon )
{
}

Coordinate::Coordinate(double degrees_lat, double degrees_lon)
: lat( degrees_lat )
, lon( degrees_lon )
{
}

const Latitude& Coordinate::getLatitude() const
{
  return lat;
}

void Coordinate::setLatitude(const Latitude& lat)
{
  this->lat = lat;
}

const Longitude& Coordinate::getLongitude() const
{
  return lon;
}

void Coordinate::setLongitude(const Longitude& lon)
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
