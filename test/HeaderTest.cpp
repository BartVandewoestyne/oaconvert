#include "HeaderTest.h"
#include "header.h"

CPPUNIT_TEST_SUITE_REGISTRATION( HeaderTest );

void
HeaderTest::setUp()
{
}

void
HeaderTest::tearDown()
{
}

void
HeaderTest::testWriteHeader()
{
  Header h;
  h.write();
}
