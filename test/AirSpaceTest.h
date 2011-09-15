#ifndef AIRSPACETEST_H
#define AIRSPACETEST_H

#include <cppunit/extensions/HelperMacros.h>

class AirSpaceTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( AirSpaceTest );
  CPPUNIT_TEST( testSetGetName );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testSetGetName();

};

#endif // AIRSPACETEST_H
