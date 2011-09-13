#ifndef COORDINATE_H
#define COORDINATE_H 

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

#include "latitude.h"
#include "longitude.h"

class Coordinate {

  private:
    Latitude lat;
    Longitude lon;

  public:
    Coordinate();
    Coordinate(std::string);
    Coordinate(Latitude lat, Longitude lon);
    Latitude getLatitude();
    void setLatitude(Latitude lat);
    Longitude getLongitude();
    void setLongitude(Longitude lon);
    bool operator ==(const Coordinate& other) const;
    friend ostream& operator <<(ostream& outputStream, const Coordinate& c);

};

#endif /* COORDINATE_H */
