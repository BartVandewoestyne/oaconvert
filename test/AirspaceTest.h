#ifndef AIRSPACETEST_H
#define AIRSPACETEST_H

#include <cppunit/extensions/HelperMacros.h>

class AirspaceTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( AirspaceTest );
  CPPUNIT_TEST( testSetGetName );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testSetGetName();

};

#endif // AIRSPACETEST_H
