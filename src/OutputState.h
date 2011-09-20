#ifndef OUTPUTSTATE_H 
#define OUTPUTSTATE_H 

#include <fstream>
#include "airspace.h"

class OutputState {

  public:
    OutputState();
    virtual void write(AirSpace s) const;
    virtual void writeHeader() const;

  protected:
    ofstream outStream;

};

#endif /* OUTPUTSTATE_H */
