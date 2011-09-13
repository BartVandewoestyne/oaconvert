#ifndef LATLON_H 
#define LATLON_H 

#include <iostream>
using namespace std;

class LatLon {

  public:
    LatLon();
    LatLon(double degrees);
    LatLon(int degrees, int minutes, int seconds, char direction);
    double getAngle();
    char getDirection();
    int getDegrees();
    bool operator ==(const LatLon& other) const;
    friend ostream& operator <<(ostream& outputStream, const LatLon& l);

  private:
    double angle;   /* South pole = 0 <= angle <= 90 = North pole */
    char direction; /* N, S */

};

#endif /* LATLON_H */
