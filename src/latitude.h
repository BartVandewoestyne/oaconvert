#ifndef LATITUDE_H 
#define LATITUDE_H 

#include "latlon.h"

class Latitude : public LatLon {

  public:

    Latitude();
    Latitude(double degrees);
    Latitude(int degrees, int minutes, int seconds, char direction);
    Latitude(int degrees, double minutes, char direction);

    double getArcDegree();
    double getM();

};

#endif /* LATITUDE_H */
