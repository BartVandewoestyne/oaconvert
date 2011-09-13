#ifndef LATITUDE_H 
#define LATITUDE_H 

#include "latlon.h"

class Latitude : public LatLon {

  public:
    Latitude();
    Latitude(double degrees);
    Latitude(int degrees, int minutes, int seconds, char direction);

};

#endif /* LATITUDE_H */
