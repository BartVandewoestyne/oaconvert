#ifndef OUTPUTWRITER_H 
#define OUTPUTWRITER_H 

#include "airspace.h"
#include "OutputState.h"

class OutputWriter {

  public:
    OutputWriter();
    OutputWriter(const std::string& filename);
    OutputWriter(std::ostream& stream);

    ~OutputWriter();

    void writeHeader();
    void write(const AirSpace& s);
    void writeFooter();

  private:
    //! \param[in] state The new state. This output writer does \e not own the
    //!                  given state.
    void changeState(OutputState* state);

  private:
    OutputState* _state;

    //! If writing to file, this Writer owns the ofstream object.
    // Note: do NOT change the order of outfile and out in this header file!
    std::ofstream *outfile;

    //! The internal output stream to write to.
    std::ostream out;

};

#endif /* OUTPUTWRITER_H */
