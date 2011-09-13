#ifndef HEADERTEST_H
#define HEADERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class HeaderTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( HeaderTest );
  CPPUNIT_TEST( testWriteHeader );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testWriteHeader();

};

#endif // HEADERTEST_H
