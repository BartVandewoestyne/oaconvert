#include "OutputWriter.h"
#include "PolishState.h"
#include "airspace.h"

using namespace std;

// By default, use Polish Format.
OutputWriter::OutputWriter(ostream& stream)
:_state(PolishState::getInstance())
, out(stream.rdbuf())
{
  // By default, use Polish Format.
}

void OutputWriter::write(const AirSpace &s) const
{
  _state->write(s);
}

void OutputWriter::writeHeader() const
{
  _state->writeHeader();
}
