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

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ParserTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( ParserTest );
  CPPUNIT_TEST( testParseCoordinate );
  CPPUNIT_TEST( testParseAltitude );
  CPPUNIT_TEST( testParseAirspaceClass );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testParseCoordinate();
  void testParseAltitude();
  void testParseAirspaceClass();

};

#endif // PARSERTEST_H
