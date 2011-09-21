#ifndef POLISHSTATE_H 
#define POLISHSTATE_H 

#include "OutputState.h"
#include "constants.h"

class PolishState : public OutputState {

  public:
    static PolishState* getInstance();

    virtual void writeHeader(std::ostream &out) const;

    virtual void write(std::ostream &out, const AirSpace& s) const;
    virtual void write(std::ostream &out, const Coordinate& c) const;
    virtual void write(std::ostream &out, const Polygon& p, const std::string &label) const;

  protected:
    PolishState();

  private:
    static PolishState* _instance;

};

#endif /* POLISHSTATE_H */
