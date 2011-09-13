#ifndef LATLONTEST_H
#define LATLONTEST_H

#include <cppunit/extensions/HelperMacros.h>

class LatLonTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( LatLonTest );
  CPPUNIT_TEST( testGetDegrees );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testGetDegrees();

};

#endif // LATLONTEST_H
