#include "CoordinateTest.h"
#include "Coordinate.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( CoordinateTest );

void
CoordinateTest::setUp()
{
}

void
CoordinateTest::tearDown()
{
}

// TODO: add more distance tests here, to check how accurate we are!
void
CoordinateTest::testGetDistance()
{
  // Best accuracy that we can seem to get is 47 metres for now...
  const double tolerance = 47.0;

  // See http://www.movable-type.co.uk/scripts/latlong.html
  Coordinate c1(Latitude(50,  3, 59, 'N'), Longitude(5, 42, 53, 'W'));
  Coordinate c2(Latitude(58, 38, 38, 'N'), Longitude(3,  4, 12, 'W'));
  double d = c1.getDistance(c2);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(968900.0, d, tolerance);
}
