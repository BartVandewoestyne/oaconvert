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

#include <iostream>
#include "ParserTest.h"
#include "parser.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( ParserTest );

void
ParserTest::setUp()
{
}

void
ParserTest::tearDown()
{
}

void
ParserTest::testGetCoordinate()
{
  Latitude lat;
  Longitude lon;
  Parser p;
  Coordinate c1, c2;

  lat = Latitude(12, 34, 56, 'N');
  lon = Longitude(56, 34, 12, 'W');
  c1 = Coordinate(lat, lon);
  c2 = p.getCoordinate("12:34:56 N 56:34:12 W    c34");
  CPPUNIT_ASSERT_EQUAL(c1, c2);

  lat = Latitude(39, 36.8, 'N');
  lon = Longitude(119, 46.1, 'W');
  c1 = Coordinate(lat, lon);
  c2 = p.getCoordinate("39:36.8 N 119:46.1W");
  CPPUNIT_ASSERT_EQUAL(c1, c2);

  lat = Latitude(49, 24.0, 'N');
  lon = Longitude(6, 8.0, 'E');
  c1 = Coordinate(lat, lon);
  c2 = p.getCoordinate("49:24.000N,006:08.000E");
  CPPUNIT_ASSERT_EQUAL(c1, c2);

  /* We currently not allow this... but since there's no ambiguity, we
     could as well allow it... */
  //lat = Latitude(12, 34, 56, 'N');
  //lon = Longitude(56, 34, 12, 'W');
  //c1 = Coordinate(lat, lon);
  //c2 = p.getCoordinate("12:34:56N56:34:12W    c34");
  //CPPUNIT_ASSERT_EQUAL(c1, c2);
}

void
ParserTest::testSetGetCurrentAirspace()
{
  Parser p;
  p.getCurrentAirspace()->setName("TestName1");
  CPPUNIT_ASSERT_EQUAL(string("TestName1"), p.getCurrentAirspace()->getName());
}
