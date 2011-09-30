#ifndef COORDINATETEST_H
#define COORDINATETEST_H

#include <cppunit/extensions/HelperMacros.h>

class CoordinateTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( CoordinateTest );
  CPPUNIT_TEST( testGetDistance );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
  void testGetDistance();

};

#endif // COORDINATETEST_H
