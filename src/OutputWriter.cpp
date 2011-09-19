#include "outputwriter.h"
#include "PolishState.h"
#include "airspace.h"

OutputWriter::OutputWriter()
{
  // By default, use Polish Format.
  _state = PolishState::getInstance();
}


OutputWriter::write(AirSpace s)
{
  _state->write(s);
}
