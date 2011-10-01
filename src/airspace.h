#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <string>
#include <utility>
#include <vector>

#include "Arc.h"
#include "Circle.h"
#include "Coordinate.h"

class AirSpace {
  public:
    typedef std::pair<std::string,Coordinate> label_type;

  private:
    std::string name;
    std::string clss;

    // TODO: probably, these should change to doubles (representing stuff in metres).
    std::string ceiling;
    std::string floor;

    //! Closed region defining the restricted airspace.
    Region* region;

    //! Collection of string labels with associated position.
    std::vector<label_type> labelCoordinates;

  public:

    AirSpace();
    ~AirSpace();

    const std::string& getName() const;
    const std::string& getClass() const;
    const std::string& getCeiling() const;
    const std::string& getFloor() const;
    const Region* GetRegion() const;

    void setName(const std::string& mystring);
    void setClass(const std::string& clss);
    void setCeiling(const std::string& ceiling);
    void setFloor(const std::string& floor);

    /**
     * Add the region to this airspace (and pass ownership of the pointer).
     */
    void add( Region* region );

    /**
     * Each airspace can have multiple name-labels that each have their location
     * on a map.  With this method, you can add locations for these labels.
     */
    void addLabelCoordinate(const std::string& label, const Coordinate& c);

    void clear();

    friend std::ostream& operator <<(std::ostream& outputStream, const AirSpace& l);

};

#endif /* AIRSPACE_H */
