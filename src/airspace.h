#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <string>
#include <vector>
#include "point.h"
//#include "coordinate.h"

using namespace std;

class AirSpace {

  private:
    string name;
    string clss;
    string ceiling;
    string floor;
    //Coordinate *coordPtr;
    std::vector<Point> points;

  public:

    AirSpace();

    void setName(string);
    string getName();
    void setCeiling(string);
    string getCeiling();
    void setFloor(string);
    string getFloor();
    void setClass(string);
    string getClass();
    void setCeiling(int);
    void setFloor(int);
    void handleLine(string);
    void addPoint(Point);
    void clear();
    friend ostream& operator <<(ostream& outputStream, const AirSpace& l);

};

#endif /* AIRSPACE_H */
