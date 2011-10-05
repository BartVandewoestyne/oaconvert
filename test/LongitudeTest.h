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

#ifndef LONGITUDETEST_H
#define LONGITUDETEST_H

#include <cppunit/extensions/HelperMacros.h>

class LongitudeTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( LongitudeTest );
  CPPUNIT_TEST( testGetArcDegree );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testGetArcDegree();

};

#endif // LONGITUDETEST_H
