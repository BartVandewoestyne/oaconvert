#include "AirspaceTest.h"
#include "Airspace.h"

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
