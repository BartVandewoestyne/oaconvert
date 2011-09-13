#ifndef LONGITUDE 
#define LONGITUDE

#include "latlon.h"

class Longitude : public LatLon {

  public:
    Longitude();
    Longitude(double degrees);
    Longitude(int degrees, int minutes, int seconds, char direction);

};

#endif /* LONGITUDE_H */
