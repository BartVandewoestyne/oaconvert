#ifndef LONGITUDETEST_H
#define LONGITUDETEST_H

#include <cppunit/extensions/HelperMacros.h>

class LongitudeTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( LongitudeTest );
  CPPUNIT_TEST( testGetArcDegree );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testGetArcDegree();

};

#endif // LONGITUDETEST_H
