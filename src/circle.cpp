#include <cmath>
#include "circle.h"

Circle::Circle()
{}

Circle::Circle(Coordinate c1, double radius)
{}

/*
 * Return the radius in nautical miles.
 */
double Circle::getRadiusNM()
{
  return radius;
}

/*
 * Return the radius in metres.
 */
double Circle::getRadiusM()
{
  return radius*1852.0;
}

void Circle::setRadiusNM(double r)
{
  radius = r;
}

void Circle::setCenter(Coordinate c)
{
  center = c;
}

Coordinate& Circle::getCenter()
{
  return center;
}

void Circle::toPolish() const
{
  int steps = 100; /* Same resolution as oa2gm */
  double globeR = 6371e3;
  const double pi = 3.14159265;
  double deg_x, deg_y;
  double angle;

  double angle_lat = getCenter().getLatitude().getAngle();
  double angle_lon = getCenter().getLongitude().getAngle();

  // Calculate how many meters 1 degree lat and long are.
  double x_res = 2*pi*( globeR*cos(pi*angle_lat/180) )/360;
  double y_res = 2*pi*globeR/360;


  for (int i = 0; i < steps; i++)
  {
    angle = i*360.0/steps;

    deg_x = angle_lon + getRadiusM()*cos(pi*angle/180)/x_res;
    deg_y = angle_lat + getRadiusM()*sin(pi*angle/180)/y_res;
    Coordinate c(deg_x, deg_y);
    cout << c << endl;
  }


}

ostream& operator <<(ostream& outputStream, const Circle& c)
{
  outputStream << "Circle:" << endl;
  outputStream << "  " << c.center << endl;
  outputStream << "  Radius in NM: " << c.radius;
  return outputStream;
}
