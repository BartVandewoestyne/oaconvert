#ifndef LATLON_H 
#define LATLON_H 

#include <iostream>

class LatLon {

  public:
    LatLon();
    LatLon(double degrees);
    LatLon(int degrees, int minutes, int seconds, char direction);
    LatLon(int degrees, double minutes, char direction);

    double getAngle() const;
    char getDirection() const;
    void setDirection(char c);
    int getDegrees() const;

    bool operator ==(const LatLon& other) const;
    friend std::ostream& operator <<(std::ostream& outputStream,
                                     const LatLon& l);

  private:
    double angle;
    char direction;

};

#endif /* LATLON_H */
