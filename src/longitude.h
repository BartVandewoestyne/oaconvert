#ifndef LONGITUDE 
#define LONGITUDE

#include "latlon.h"
#include "latitude.h"

class Longitude : public LatLon {

  public:
    Longitude();
    Longitude(double degrees);
    Longitude(int degrees, int minutes, int seconds, char direction);
    Longitude(int degrees, double minutes, char direction);

    double getArcDegree(const Latitude& lat);
    double getN();

};

#endif /* LONGITUDE_H */
