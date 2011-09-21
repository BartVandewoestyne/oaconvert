#ifndef OUTPUTSTATE_H 
#define OUTPUTSTATE_H 

#include <iostream>

class AirSpace;
class Coordinate;
class Polygon;

class OutputState {

  public:
    OutputState(){};
    virtual void writeHeader(std::ostream &out) const = 0;

    virtual void write(std::ostream &out, const AirSpace& s) const = 0;
    virtual void write(std::ostream &out, const Coordinate& c) const = 0;
    virtual void write(std::ostream &out, const Polygon& p, const std::string &label) const = 0;
};

#endif /* OUTPUTSTATE_H */
