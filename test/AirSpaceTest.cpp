#include "AirSpaceTest.h"
#include "airspace.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( AirSpaceTest );

void
AirSpaceTest::setUp()
{
}

void
AirSpaceTest::tearDown()
{
}

void
AirSpaceTest::testSetGetName()
{
  AirSpace s;
  s.setName("test");
  CPPUNIT_ASSERT_EQUAL(string("test"), s.getName());
  CPPUNIT_ASSERT_EQUAL(false, s.hasCircle());
  CPPUNIT_ASSERT_EQUAL(false, s.hasPolygon());
}
