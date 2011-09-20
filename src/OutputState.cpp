#include "OutputState.h"
#include "airspace.h"

OutputState::OutputState()
{
  outStream.open("output.mp");
}

void OutputState::write(AirSpace s) const
{}

void OutputState::writeHeader() const
{}
