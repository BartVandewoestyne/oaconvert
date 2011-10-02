#ifndef LATLON_H 
#define LATLON_H 

#include <iostream>

/**
 * Class offering common functionality to Latitude and Longitude classes.
 */
class LatLon {

  public:

    /**
     * Construct a LatLon object without angle nor direction.
     *
     * TODO: we shouldn't be able to construct these kind of objects.  How
     *       to enforce this?  In Java-terminology: how to make this an
     *       'abstract' class?
     */
    LatLon();

    /**
     * Construct a LatLon object with the specified angle in decimal degrees.
     *
     * @param degrees Angle in degrees.
     */
    LatLon(double degrees);
    LatLon(int degrees, double minutes, char direction);
    LatLon(int degrees, int minutes, int seconds, char direction);

    double getAngle() const;
    char getDirection() const;
    int getDegrees() const;
    int getMinutes() const;
    double getSeconds() const;
    const double toRadians() const;

    void setDirection(char c);

    bool operator ==(const LatLon& other) const;
    friend std::ostream& operator <<(std::ostream& outputStream,
                                     const LatLon& l);

  private:
    double angle;
    char direction;

};

#endif /* LATLON_H */
