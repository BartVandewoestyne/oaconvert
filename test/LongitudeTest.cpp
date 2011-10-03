#include "LongitudeTest.h"
#include "latitude.h"
#include "longitude.h"

CPPUNIT_TEST_SUITE_REGISTRATION( LongitudeTest );

void
LongitudeTest::setUp()
{
}

void
LongitudeTest::tearDown()
{
}

/*
 * Tests based on values returned from
 * http://www.csgnetwork.com/degreelenllavcalc.html
 */
void
LongitudeTest::testGetArcDegree()
{
  // The best we can agree with the results from the above website...
  double tol = 221.0;

  // Longitude doesn't really matter.
  Longitude lon(45, 00, 00, 'N');

  Latitude lat;

  lat = Latitude(45, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(78846.80572069259, lon.getArcDegree(lat), tol);

  lat = Latitude(20, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(104647.05311831612, lon.getArcDegree(lat), tol);

  lat = Latitude(60, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(55799.979000000014, lon.getArcDegree(lat), tol);
}
