#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <string>
#include <vector>
#include "polygon.h"
#include "circle.h"
#include "arc.h"
#include "coordinate.h"

class AirSpace {

  private:
    std::string name;
    std::string clss;
    std::string ceiling;
    std::string floor;
    Polygon polygon;
    Circle circle;
    Arc arc;
    std::vector<Coordinate> labelCoordinates;

  public:

    AirSpace();

    void setName(const std::string& mystring);
    const std::string &getName() const;
    void setCeiling(const std::string& ceiling);
    const std::string& getCeiling() const;

    const Polygon& getPolygon() const;
    Polygon& getPolygon();
    const Circle& getCircle() const;
    Circle& getCircle();
    const Arc& getArc() const;
    Arc& getArc();

    void setFloor(const std::string& floor);
    const std::string& getFloor() const;
    void setClass(const std::string& clss);
    const std::string& getClass() const;
    void setCeiling(int ceil);
    void setFloor(int floor);
    void addLabelCoordinate(const Coordinate& c);
    void clear();
    bool hasPolygon() const;
    bool hasCircle() const;
    friend std::ostream& operator <<(std::ostream& outputStream, const AirSpace& l);

};

#endif /* AIRSPACE_H */
