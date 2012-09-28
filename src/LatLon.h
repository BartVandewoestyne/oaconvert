/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.

  This file is part of oaconvert.

  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LATLON_H
#define LATLON_H

#include <iostream>

/**
 * Class offering common functionality to Latitude and Longitude classes.
 */
class LatLon
{

public:

    /**
     * Construct a LatLon object with the specified angle in decimal degrees.
     *
     * @param degrees Angle in degrees.
     */
    LatLon(double angle);
    LatLon(int degrees, double minutes);
    LatLon(int degrees, int minutes, double seconds);

    virtual ~LatLon();

    double getAngle() const;
    int getDegrees() const;
    int getMinutes() const;
    double getSeconds() const;
    double toRadians() const;

    virtual char getDirection() const = 0;

    bool operator ==(const LatLon& other) const;
    friend std::ostream& operator <<(std::ostream& outputStream,
                                     const LatLon& l);

protected:

    double angle;

};

#endif /* LATLON_H */
