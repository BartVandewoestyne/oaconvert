#include <iostream>
#include "ParserTest.h"
#include "parser.h"

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

  lat = Latitude(39, 24.0, 'N');
  lon = Longitude(6, 8.0, 'E');
  c1 = Coordinate(lat, lon);
  c2 = p.getCoordinate("49:24.000N,006:08.000E");
  CPPUNIT_ASSERT_EQUAL(c1, c2);
}

void
ParserTest::testSetGetCurrentAirSpace()
{
  Parser p;
  p.getCurrentAirSpace().setName("TestName1");
  CPPUNIT_ASSERT_EQUAL(string("TestName1"), p.getCurrentAirSpace().getName());
}
