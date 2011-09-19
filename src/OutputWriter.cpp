#include "OutputWriter.h"
#include "PolishState.h"
#include "airspace.h"

OutputWriter::OutputWriter()
{
  // By default, use Polish Format.
  _state = PolishState::getInstance();
}


void OutputWriter::write(AirSpace s)
{
  _state->write(s);
}
