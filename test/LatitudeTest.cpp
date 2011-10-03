#include "LatitudeTest.h"
#include "latitude.h"
#include "longitude.h"

CPPUNIT_TEST_SUITE_REGISTRATION( LatitudeTest );

void
LatitudeTest::setUp()
{
}

void
LatitudeTest::tearDown()
{
}

/*
 * Tests based on values returned from
 * http://www.csgnetwork.com/degreelenllavcalc.html
 */
void
LatitudeTest::testGetArcDegree()
{
  // The best we can agree with the results from the above website...
  double tol = 491.0;

  // Longitude doesn't really matter.
  Longitude lon(45, 00, 00, 'N');

  Latitude lat;

  lat = Latitude(45, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(111131.745, lat.getArcDegree(), tol);

  lat = Latitude(20, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(110704.27818646189, lat.getArcDegree(), tol);

  lat = Latitude(60, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(111412.24020000001, lat.getArcDegree(), tol);
}
