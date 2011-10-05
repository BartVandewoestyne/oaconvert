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

#include "LatLonTest.h"
#include "latlon.h"

CPPUNIT_TEST_SUITE_REGISTRATION( LatLonTest );

void
LatLonTest::setUp()
{
}

void
LatLonTest::tearDown()
{
}

void
LatLonTest::testGetDegrees()
{
  LatLon l1(12, 34, 56, 'N');
  CPPUNIT_ASSERT( l1.getDegrees() == 12);

  LatLon l2(12, 34, 56, 'S');
  CPPUNIT_ASSERT( l2.getDegrees() == -12);
}
