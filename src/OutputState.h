#ifndef OUTPUTSTATE_H 
#define OUTPUTSTATE_H 

#include "airspace.h"

class OutputState {

  public:
    OutputState();
    virtual void write(AirSpace s) const;

};

#endif /* OUTPUTSTATE_H */
