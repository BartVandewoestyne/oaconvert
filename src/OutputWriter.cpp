#include "OutputWriter.h"

#include <fstream>
#include "Airspace.h"
#include "assert.h"
#include "PolishState.h"

using namespace std;

OutputWriter::OutputWriter()
:_state(PolishState::getInstance())
, outfile(0)
, out(cout.rdbuf())
  {
  }


OutputWriter::OutputWriter(const std::string& filename)
:_state(PolishState::getInstance())
, outfile(new std::ofstream(filename.c_str()))
, out(outfile->rdbuf())
  {
  }


OutputWriter::OutputWriter(std::ostream& stream)
:_state(PolishState::getInstance())
, outfile(0)
, out(stream.rdbuf())
{
}


OutputWriter::~OutputWriter()
  {
  if( outfile )
    {
    outfile->close();
    }
  delete outfile;
  }


void OutputWriter::changeState(OutputState* state)
  {
  _state = state;
  }


void OutputWriter::writeHeader()
{
  _state->writeHeader(out);
}


void OutputWriter::write(const Airspace &s)
{
  // TODO
//  ASSERT( ! "TODO" );
  _state->write(out, s);
}


void OutputWriter::writeFooter()
  {
  // TODO
//  ASSERT( ! "TODO" );
  }
