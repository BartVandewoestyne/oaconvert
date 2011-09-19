#include "PolishState.h"
#include "airspace.h"
using Constants::pi;


PolishState* PolishState::_instance = 0;

PolishState::PolishState()
{
  cout << "PolishState()" << endl;
}


void PolishState::write(AirSpace s) const
{
  cout << "PolishState::write(AirSpace s)" << endl;
  write(s.getPolygon());
  write(s.getCircle());;
}

PolishState* PolishState::getInstance()
{
  if (_instance == 0)
  {
    _instance = new PolishState;
  }
  return _instance;
}

void PolishState::write(Polygon p) const
{
  // See section 4.2.4.2 in http://cgpsmapper.com/download/cGPSmapper-UsrMan-v02.1.pdf
  cout << "[POLYGON]" << endl;
  cout << "Type=0x0a" << endl; // use same as oa2gm source code, figure out later why...
  cout << "Data0=" << endl;
  // TODO: loop over p.coords and plot all coordinates in this polygon.
  cout << "[END]" << endl;
}


/*
 * See http://en.wikipedia.org/wiki/Latitude#Degree_length
 *
 * TODO: check if these calculatiosn (based on the oa2gm source code) are
 *       correct.  I guess not, because they both use 6371e3 for computing
 *       new latitudinal and longitudinal points.  This is not 100% correct.
 *       We should probably follow WGS84 or IERS 2003 ellipsoids.
 */
void PolishState::write(Circle c) const
{
  // Resolution of the circle.  Currently, we use the same value as the
  // oa2gm program, but in the future we might make this configurable via
  // a configuration file.
  int steps = 100;

  double deg_lat, deg_lon;
  double angle;

  Latitude lat = c.getCenter().getLatitude();
  Longitude lon = c.getCenter().getLongitude();

  // Compute arcdegree of latitude respectively longitude difference.
  // Note here that we assume latitudinal and longitudinal radius of the
  // earth to be the same.  It would be more precise to assume different
  // values.  See M and N-values at
  //
  //   http://en.wikipedia.org/wiki/Latitude#Degree_length
  //
  double phi = pi*lat.getAngle()/180.0;
  double arcdegree_lat = pi*lat.getM()/180;
  double arcdegree_lon = pi*cos(phi)*lon.getN()/180;

  for (int i = 0; i < steps; ++i)
  {
    angle = i*360.0/steps;

    deg_lon = lon.getAngle() + c.getRadiusM()*cos(pi*angle/180)/arcdegree_lon;
    deg_lat = lat.getAngle() + c.getRadiusM()*sin(pi*angle/180)/arcdegree_lat;
    Coordinate c(deg_lat, deg_lon);
    
  }

}
