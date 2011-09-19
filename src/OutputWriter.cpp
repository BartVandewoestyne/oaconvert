#include "OutputWriter.h"
#include "PolishState.h"
#include "airspace.h"

OutputWriter::OutputWriter():_state(PolishState::getInstance())
{
  // By default, use Polish Format.
  cout << "OutputWriter::OutputWriter()" << endl;
}


void OutputWriter::write(AirSpace s)
{
  cout << "OutputWriter::write(AirSpace s)" << endl;
  _state->write(s);
}
