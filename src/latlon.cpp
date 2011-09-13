#include "latlon.h"

LatLon::LatLon()
{
}

LatLon::LatLon(double degrees) {
  angle = degrees;
}

LatLon::LatLon(int degrees, int minutes, int seconds, char direction) {
  angle = degrees + minutes/60.0 + seconds/3600.0;
  if ( (direction == 's') || (direction == 'S') || (direction == 'W') || (direction == 'w') )
  {
    angle = -angle;
  }
}

double LatLon::getAngle() {
  return angle;
}

char LatLon::getDirection() {
  return direction;
}

int LatLon::getDegrees() {
  return (int) angle;
}

bool LatLon::operator ==(const LatLon& other) const
{
  return ( (angle == other.angle) && (direction == other.direction) );
}

ostream& operator <<(ostream& outputStream, const LatLon& l)
{
  outputStream << l.angle;
  outputStream << " ";
  outputStream << l.direction;

  return outputStream;
}
