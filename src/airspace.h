#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <string>
#include <vector>
#include "polygon.h"
#include "coordinate.h"

using namespace std;

class AirSpace {

  private:
    string name;
    string clss;
    string ceiling;
    string floor;
    Polygon polygon;
    std::vector<Coordinate> labelCoordinates;

  public:

    AirSpace();

    void setName(string);
    string getName();
    void setCeiling(string);
    string getCeiling();
    Polygon& getPolygon();
    void setFloor(string);
    string getFloor();
    void setClass(string);
    string getClass();
    void setCeiling(int);
    void setFloor(int);
    void addLabelCoordinate(Coordinate);
    void clear();
    friend ostream& operator <<(ostream& outputStream, const AirSpace& l);

};

#endif /* AIRSPACE_H */
