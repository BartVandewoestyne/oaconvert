#ifndef POLISHSTATE_H 
#define POLISHSTATE_H 

#include "OutputState.h"
#include "constants.h"

class PolishState : public OutputState {

  public:
    static PolishState* getInstance();

    virtual void write(const AirSpace& s) const;

  protected:
    PolishState();

  private:
    static PolishState* _instance;

    virtual void writeHeader() const;
    virtual void write(const Polygon& p, const std::string& label, const std::string& type) const;
    virtual void write(const Coordinate& c) const;

    std::string getType(const std::string& airspaceClass) const;

};

#endif /* POLISHSTATE_H */
