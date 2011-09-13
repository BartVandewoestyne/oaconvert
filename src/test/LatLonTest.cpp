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
