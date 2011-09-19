#include "latlon.h"
#include <string>

using namespace std;

LatLon::LatLon()
{/* Body intentionally empty. */}

LatLon::LatLon(double degrees)
{
  // TODO:
  // Since for latitudes we have that -90 <= angle <= 90 and for longitudes
  // we have that -180 <= angle <= 180, we could check here if
  //
  //   -180 <= angle <= 180
  //
  // and throw an exception if this condition is not satisfied?
  angle = degrees;
}

LatLon::LatLon(int degrees, int minutes, int seconds, char direction)
{
  angle = degrees + minutes/60.0 + seconds/3600.0;
  if ( (direction == 's')
      || (direction == 'S')
      || (direction == 'W')
      || (direction == 'w') )
  {
    angle = -angle;
  }
  this->direction = direction;
}

LatLon::LatLon(int degrees, double minutes, char direction)
{
  angle = degrees + minutes/60.0;
  if ( (direction == 's')
      || (direction == 'S')
      || (direction == 'W')
      || (direction == 'w') )
  {
    angle = -angle;
  }
  this->direction = direction;
}

double LatLon::getAngle() const {
  return angle;
}

char LatLon::getDirection() const {
  return direction;
}

void LatLon::setDirection(char c)
{
  direction = c;
}

int LatLon::getDegrees() const {
  return (int) angle; // ? What is difference between getangles and getdegrees?
}

bool LatLon::operator ==(const LatLon& other) const
{
  return ( (angle == other.angle) && (direction == other.direction) );
}

ostream& operator <<(ostream& outputStream, const LatLon& l)
{
  string dirstring(1,l.direction);

  outputStream << l.angle;
  outputStream << " ";
  outputStream << dirstring;

  return outputStream;
}
