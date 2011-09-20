#ifndef OUTPUTSTATE_H 
#define OUTPUTSTATE_H 

#include <fstream>
#include "airspace.h"

class OutputState {

  public:
    OutputState();
    virtual void write(const AirSpace& s) const = 0;
    virtual void writeHeader() const = 0;

  protected:
    std::ofstream outStream;

};

#endif /* OUTPUTSTATE_H */
