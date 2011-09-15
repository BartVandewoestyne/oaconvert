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
  Latitude lat = Latitude(12, 34, 56, 'N');
  Longitude lon = Longitude(56, 34, 12, 'W');
  Coordinate c1 = Coordinate(lat, lon);

  Parser p;
  Coordinate c2 = p.getCoordinate("12:34:56 N 56:34:12 W    c34");
  CPPUNIT_ASSERT_EQUAL(c1, c2);
}

void
ParserTest::testSetGetCurrentAirSpace()
{
  Parser p;
  p.getCurrentAirSpace().setName("TestName1");
  CPPUNIT_ASSERT_EQUAL(string("TestName1"), p.getCurrentAirSpace().getName());
}
