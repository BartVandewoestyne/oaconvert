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

    const std::string& getName() const;
    const std::string& getClass() const;
    const std::string& getCeiling() const;
    const std::string& getFloor() const;
    const Polygon& getPolygon() const;
    const Circle& getCircle() const;
    const Arc& getArc() const;

    void setName(const std::string& mystring);
    void setClass(const std::string& clss);
    void setCeiling(const std::string& ceiling);
    void setFloor(const std::string& floor);

    bool hasPolygon() const;
    bool hasCircle() const;
    void addLabelCoordinate(const Coordinate& c);
    void clear();

    friend std::ostream& operator <<(std::ostream& outputStream, const AirSpace& l);

};

#endif /* AIRSPACE_H */
