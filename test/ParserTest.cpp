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
#include "Parser.h"
#include "Constants.h"

using namespace std;
using namespace Constants;

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
ParserTest::testParseCoordinate()
{
  Latitude lat;
  Longitude lon;
  Parser p;
  Coordinate c1, c2;

  lat = Latitude(12, 34, 56, 'N');
  lon = Longitude(56, 34, 12, 'W');
  c1 = Coordinate(lat, lon);
  c2 = p.parseCoordinate("12:34:56 N 56:34:12 W    c34");
  CPPUNIT_ASSERT_EQUAL(c1, c2);

  lat = Latitude(12, 34, 56.3, 'N');
  lon = Longitude(56, 34, 12.6, 'W');
  c1 = Coordinate(lat, lon);
  c2 = p.parseCoordinate("12:34:56.3 N 56:34:12.6 W    c34");
  CPPUNIT_ASSERT_EQUAL(c1, c2);

  lat = Latitude(39, 36.8, 'N');
  lon = Longitude(119, 46.1, 'W');
  c1 = Coordinate(lat, lon);
  c2 = p.parseCoordinate("39:36.8 N 119:46.1W");
  CPPUNIT_ASSERT_EQUAL(c1, c2);

  lat = Latitude(49, 24.0, 'N');
  lon = Longitude(6, 8.0, 'E');
  c1 = Coordinate(lat, lon);
  c2 = p.parseCoordinate("49:24.000N,006:08.000E");
  CPPUNIT_ASSERT_EQUAL(c1, c2);

  /* We currently do not allow this one because it simply doesn't look nice,
     but since there's no ambiguity, we could as well allow it and give a
     warning... */
  // TODO: Throw an exception if we see this kind of coordinate specification and
  //       check here with CPPUNIT_ASSERT_THROW.
  //lat = Latitude(12, 34, 56, 'N');
  //lon = Longitude(56, 34, 12, 'W');
  //c1 = Coordinate(lat, lon);
  //c2 = p.parseCoordinate("12:34:56N56:34:12W    c34");
  //CPPUNIT_ASSERT_EQUAL(c1, c2);

  /* We currently do not allow this one because in DD:MM:SS we have that
   *   0 <= MM < 60
   * and there's no need to use 3 digits.  For now, the program exits, but
   * we could give a warning...
   */
  // TODO: Throw an exception if we see this kind of coordinate specification and
  //       check here with CPPUNIT_ASSERT_THROW.
  //lat = Latitude(50, 59, 57, 'N');
  //lon = Longitude(5, 3, 55, 'E');
  //c1 = Coordinate(lat, lon);
  //c2 = p.parseCoordinate("50:59:57N 005:003:55E");
  //CPPUNIT_ASSERT_EQUAL(c1, c2);
}

void
ParserTest::testParseAltitude()
{
  // We want an accuracy of 1 meter.
  double tol = 1;

  Parser p;
  double alt;

  alt = p.parseAltitude("03500 FT MSL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(3500*feet_in_meter, alt, tol);

  alt = p.parseAltitude("10000ft MSL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(10000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("04500MSL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(4500*feet_in_meter, alt, tol);

  alt = p.parseAltitude("2000 ft AMSL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("3000 ft");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(3000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("15000ft (Mo-Fri)");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(15000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("FL55");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(5500*feet_in_meter, alt, tol);

  alt = p.parseAltitude("FL 100");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(10000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("1000 AGL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("1000 FT AGL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("1000FT AGL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1000*feet_in_meter, alt, tol);

  alt = p.parseAltitude("Ask on 122.8");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, alt, tol);

  alt = p.parseAltitude("UNL");
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, alt, tol);

  /* These should not pass. */
  alt = p.parseAltitude("55 FL");

}

void
ParserTest::testParseAirspaceClass()
{
  Parser p;
  std::string aclass;

  aclass = p.parseAirspaceClass("A");
  CPPUNIT_ASSERT("A" == aclass);

  aclass = p.parseAirspaceClass("B");
  CPPUNIT_ASSERT("B" == aclass);

  aclass = p.parseAirspaceClass("C");
  CPPUNIT_ASSERT("C" == aclass);

  aclass = p.parseAirspaceClass("D");
  CPPUNIT_ASSERT("D" == aclass);

  aclass = p.parseAirspaceClass("E");
  CPPUNIT_ASSERT("E" == aclass);

  aclass = p.parseAirspaceClass("F");
  CPPUNIT_ASSERT("F" == aclass);

  aclass = p.parseAirspaceClass("G");
  CPPUNIT_ASSERT("G" == aclass);

  aclass = p.parseAirspaceClass("P");
  CPPUNIT_ASSERT("P" == aclass);

  aclass = p.parseAirspaceClass("Q");
  CPPUNIT_ASSERT("Q" == aclass);

  aclass = p.parseAirspaceClass("R");
  CPPUNIT_ASSERT("R" == aclass);

  aclass = p.parseAirspaceClass("W");
  CPPUNIT_ASSERT("W" == aclass);

  aclass = p.parseAirspaceClass("GP");
  CPPUNIT_ASSERT("GP" == aclass);

  aclass = p.parseAirspaceClass("CTR");
  CPPUNIT_ASSERT("CTR" == aclass);

  aclass = p.parseAirspaceClass("CTR");
  CPPUNIT_ASSERT("CTR" == aclass);

}

void
ParserTest::testSetGetCurrentAirspace()
{
  Parser p;
  p.getCurrentAirspace()->setName("TestName1");
  CPPUNIT_ASSERT_EQUAL(string("TestName1"), p.getCurrentAirspace()->getName());
}
