#ifndef OUTPUTSTATE_H 
#define OUTPUTSTATE_H 

#include <iostream>

#include "Region.h"

//class AirSpace;
//class Coordinate;
//class Polygon;
class AirSpace;
class Circle;
class CurvedPolygon;

//////////////////////////////////////////////////////////////////////////////////////////
// Interface OutputState
//////////////////////////////////////////////////////////////////////////////////////////

class OutputState {

  public:
    OutputState(){};
    virtual void writeHeader(std::ostream &out) const = 0;
    virtual void writeFooter(std::ostream &out) const = 0;


    //! Use this method to write out an airspace.
    virtual void write(std::ostream& stream, const AirSpace& airspace) const = 0;

    //! Helper methods to write out the info of an airspace.
    void write(std::ostream& stream, const Region* region) const;
    virtual void write(std::ostream& stream, const Circle* circle) const = 0;
    virtual void write(std::ostream& stream, const CurvedPolygon* curved_polygon) const = 0;

//    virtual void write(std::ostream &out, const AirSpace& s) const = 0;
//    virtual void write(std::ostream &out, const Coordinate& c) const = 0;
//    virtual void write(std::ostream &out, const Polygon& p, const std::string &label) const = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Inline functions
//////////////////////////////////////////////////////////////////////////////////////////

inline void OutputState::write(std::ostream& stream, const Region* region) const
{
//  std::cout << "OutputState::write()" << std::endl;
  if( region )
  {
    region->write(stream, this);
  }
  else
  {
    std::cout << " WARNING: Not printing airspace with empty region." << std::endl;
  }
}

#endif /* OUTPUTSTATE_H */
