/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.
  
  This file is part of oaconvert.
  
  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "LatitudeTest.h"
#include "latitude.h"
#include "longitude.h"

CPPUNIT_TEST_SUITE_REGISTRATION( LatitudeTest );

void
LatitudeTest::setUp()
{
}

void
LatitudeTest::tearDown()
{
}

/*
 * Tests based on values returned from
 * http://www.csgnetwork.com/degreelenllavcalc.html
 */
void
LatitudeTest::testGetArcDegree()
{
  // The best we can agree with the results from the above website...
  double tol = 491.0;

  // Longitude doesn't really matter.
  Longitude lon(45, 00, 00, 'N');

  Latitude lat;

  lat = Latitude(45, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(111131.745, lat.getArcDegree(), tol);

  lat = Latitude(20, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(110704.27818646189, lat.getArcDegree(), tol);

  lat = Latitude(60, 00, 00, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(111412.24020000001, lat.getArcDegree(), tol);
}
