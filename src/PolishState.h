#ifndef POLISHSTATE_H 
#define POLISHSTATE_H 

#include "OutputState.h"
#include "constants.h"

class PolishState : public OutputState {

  public:
    static OutputState* getInstance();

    virtual void write(AirSpace s) const;
    virtual void write(Polygon p) const;
    virtual void write(Circle c) const;

};

#endif /* POLISHSTATE_H */
