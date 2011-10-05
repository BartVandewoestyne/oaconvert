/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.
  
  This file is part of oaconvert.
  
  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

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
