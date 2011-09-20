#include "OutputWriter.h"
#include "PolishState.h"
#include "airspace.h"

// By default, use Polish Format.
OutputWriter::OutputWriter(ostream& stream)
:_state(PolishState::getInstance())
, out(stream.rdbuf())
{}

void OutputWriter::write(AirSpace s) const
{
  _state->write(s);
}

void OutputWriter::writeHeader() const
{
  _state->writeHeader();
}
