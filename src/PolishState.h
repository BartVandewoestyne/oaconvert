#ifndef POLISHSTATE_H 
#define POLISHSTATE_H 

#include "OutputState.h"
#include "constants.h"

class PolishState : public OutputState {

  public:
    static PolishState* getInstance();

    virtual void writeHeader() const;
    virtual void write(const AirSpace& s) const;
    virtual void write(const Polygon& p, const std::string &label) const;
    virtual void write(const Coordinate& c) const;

  protected:
    PolishState();

  private:
    static PolishState* _instance;

};

#endif /* POLISHSTATE_H */
