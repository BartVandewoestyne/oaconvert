#ifndef LATITUDETEST_H
#define LATITUDETEST_H

#include <cppunit/extensions/HelperMacros.h>

class LatitudeTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( LatitudeTest );
  CPPUNIT_TEST( testGetArcDegree );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testGetArcDegree();

};

#endif // LATITUDETEST_H
