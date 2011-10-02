#include "OutputWriter.h"

#include <cassert>
#include <fstream>

#include "airspace.h"
#include "PolishState.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////
// Implementation OutputWriter
//////////////////////////////////////////////////////////////////////////////////////////

OutputWriter::OutputWriter()
:_state(PolishState::getInstance())
, outfile(0)
, out(cout.rdbuf())
  {
  }

//----------------------------------------------------------------------------------------
OutputWriter::OutputWriter(const std::string& filename)
:_state(PolishState::getInstance())
, outfile(new std::ofstream(filename.c_str()))
, out(outfile->rdbuf())
  {
  std::cout << "OutputWriter::OutputWriter(filename=" << filename << ")" << std::endl;
  }

//----------------------------------------------------------------------------------------
OutputWriter::OutputWriter(std::ostream& stream)
:_state(PolishState::getInstance())
, outfile(0)
, out(stream.rdbuf())
{
}

//----------------------------------------------------------------------------------------
OutputWriter::~OutputWriter()
  {
  if( outfile )
    {
    outfile->close();
    }
  delete outfile;
  }

//----------------------------------------------------------------------------------------
void OutputWriter::changeState(OutputState* state)
  {
  _state = state;
  }

//----------------------------------------------------------------------------------------
void OutputWriter::writeHeader()
{
  _state->writeHeader(out);
}

//----------------------------------------------------------------------------------------
void OutputWriter::write(const AirSpace &s)
{
  // TODO
//  assert( ! "TODO" );
  _state->write(out, s.getRegion());
}

//----------------------------------------------------------------------------------------
void OutputWriter::writeFooter()
  {
  // TODO
//  assert( ! "TODO" );
  }

