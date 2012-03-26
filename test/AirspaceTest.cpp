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

#include "AirspaceTest.h"
#include "Airspace.h"
#include "Coordinate.h"
#include "Label.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( AirspaceTest );

void
AirspaceTest::setUp()
{
}

void
AirspaceTest::tearDown()
{
}

void
AirspaceTest::testSetGetName()
{
  Airspace s;
  s.setName("test");
  CPPUNIT_ASSERT_EQUAL(string("test"), s.getName());
  //CPPUNIT_ASSERT_EQUAL(false, s.hasCircle()); // older methods
  //CPPUNIT_ASSERT_EQUAL(false, s.hasPolygon()); // older methods
}

void
AirspaceTest::testCoutOperator()
{
  Airspace s;
  Coordinate c1(Latitude(50,  3, 59, 'N'), Longitude(5, 42, 53, 'W'));

  s.setName("test");
  s.add(Label("Testlabel", c1));

  cout << s << endl;
}
