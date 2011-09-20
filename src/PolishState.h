#ifndef POLISHSTATE_H 
#define POLISHSTATE_H 

#include "OutputState.h"
#include "constants.h"

class PolishState : public OutputState {

  public:
    static PolishState* getInstance();

    virtual void writeHeader() const;
    virtual void write(AirSpace s) const;
    virtual void write(Polygon p, std::string label) const;
    virtual void write(Coordinate c) const;

  protected:
    PolishState();

  private:
    static PolishState* _instance;

};

#endif /* POLISHSTATE_H */
