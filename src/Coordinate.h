#ifndef COORDINATE_H
#define COORDINATE_H 

#include <iostream>
#include <stdlib.h>
#include <string>

#include "latitude.h"
#include "longitude.h"

class Coordinate {

  private:
    Latitude lat;
    Longitude lon;

  public:
    Coordinate();
    Coordinate(std::string);
    Coordinate(const Latitude& lat, const Longitude& lon);
    Coordinate(double degrees_lat, double degrees_lon);

    const Latitude& getLatitude() const;
    const Longitude& getLongitude() const;

    void setLatitude(const Latitude& lat);
    void setLongitude(const Longitude& lon);

    void toPolish(std::ostream& outputStream) const;
    double getDistance(const Coordinate& c) const;

    bool operator ==(const Coordinate& other) const;
    friend std::ostream& operator <<(std::ostream& outputStream, const Coordinate& c);

};

#endif /* COORDINATE_H */
