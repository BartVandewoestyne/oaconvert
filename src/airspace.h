#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <string>
#include <vector>
#include "polygon.h"
#include "circle.h"
#include "coordinate.h"

using namespace std;

class AirSpace {

  private:
    string name;
    string clss;
    string ceiling;
    string floor;
    Polygon polygon;
    Circle circle;
    std::vector<Coordinate> labelCoordinates;

  public:

    AirSpace();

    void setName(string);
    string getName() const;
    void setCeiling(string);
    string getCeiling() const;
    Polygon& getPolygon();
    Circle& getCircle();
    void setFloor(string);
    string getFloor() const;
    void setClass(string);
    string getClass() const;
    void setCeiling(int);
    void setFloor(int);
    void addLabelCoordinate(Coordinate);
    void clear();
    friend ostream& operator <<(ostream& outputStream, const AirSpace& l);

};

#endif /* AIRSPACE_H */
