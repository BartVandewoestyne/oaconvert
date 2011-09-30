#include <string>
#include "latlon.h"
#include "constants.h"

using namespace std;
using Constants::pi;

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

/**
 * Return the complete angle as a floating point number.
 */
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

/**
 * Return the integer value for the degrees (the DD in DD:MM:SS, which is
 * equal to getAngle() minus its fractional part).
 */
int LatLon::getDegrees() const
{
  return (int) angle; // ? What is difference between getangles and getdegrees?
}

/**
 * Return the angle in radians.
 */
const double LatLon::toRadians() const
{
  return pi*angle/180.0;
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
