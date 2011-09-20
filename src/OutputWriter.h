#ifndef OUTPUTWRITER_H 
#define OUTPUTWRITER_H 

#include "airspace.h"
#include "OutputState.h"

class OutputWriter {

  public:
    OutputWriter(std::ostream& stream);

    void write(AirSpace s) const;
    void writeHeader() const;

  private:
    void changeState(OutputState*);

  private:
    OutputState* _state;
    std::ostream out;

};

#endif /* OUTPUTWRITER_H */
