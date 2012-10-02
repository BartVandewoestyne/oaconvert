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

#include "LatLonTest.h"
#include "LatLon.h"
#include "Latitude.h"
#include "Longitude.h"

CPPUNIT_TEST_SUITE_REGISTRATION( LatLonTest );

void
LatLonTest::setUp()
{
}

void
LatLonTest::tearDown()
{
}

void
LatLonTest::testGetAngle()
{
  double tol = 1e-12;

  Latitude lat(-12.44);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-12.44, lat.getAngle(), tol);

  lat = Latitude(14.55);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(14.55, lat.getAngle(), tol);

  Longitude lon(-45.44);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-45.44, lon.getAngle(), tol);

  lon = Longitude(56.34);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(56.34, lon.getAngle(), tol);

  lat = Latitude(12, 34, 45.12, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(12.5792, lat.getAngle(), tol);

  lat = Latitude(22, 34, 45.12, 'S');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-22.5792, lat.getAngle(), tol);

  lon = Longitude(5, 42, 53, 'E');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(5.71472222222222, lon.getAngle(), tol);

  lon = Longitude(7, 42, 53, 'W');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-7.71472222222222, lon.getAngle(), tol);
}

void
LatLonTest::testGetDegrees()
{
  Latitude lat = Latitude(12, 34, 45.12, 'N');
  CPPUNIT_ASSERT_EQUAL(12, lat.getDegrees());

  lat = Latitude(22, 34, 45.12, 'S');
  CPPUNIT_ASSERT_EQUAL(22, lat.getDegrees());

  Longitude lon = Longitude(5, 42, 53, 'E');
  CPPUNIT_ASSERT_EQUAL(5, lon.getDegrees());

  lon = Longitude(7, 42, 53, 'W');
  CPPUNIT_ASSERT_EQUAL(7, lon.getDegrees());
}

void
LatLonTest::testGetMinutes()
{
  Latitude lat = Latitude(12, 23, 45.12, 'N');
  CPPUNIT_ASSERT_EQUAL(23, lat.getMinutes());

  lat = Latitude(12, 34, 45.12, 'S');
  CPPUNIT_ASSERT_EQUAL(34, lat.getMinutes());

  Longitude lon = Longitude(34, 42, 53.23, 'E');
  CPPUNIT_ASSERT_EQUAL(42, lon.getMinutes());

  lon = Longitude(5, 56, 53.54, 'W');
  CPPUNIT_ASSERT_EQUAL(56, lon.getMinutes());
}

void
LatLonTest::testGetSeconds()
{
  double tol = 1e-12;

  Latitude lat = Latitude(12, 34, 45.12, 'N');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(45.12, lat.getSeconds(), tol);

  lat = Latitude(2, 48, 32.45, 'S');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(32.45, lat.getSeconds(), tol);

  Longitude lon = Longitude(8, 45, 26.45, 'E');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(26.45, lon.getSeconds(), tol);

  lon = Longitude(2, 48, 32.45, 'W');
  CPPUNIT_ASSERT_DOUBLES_EQUAL(32.45, lon.getSeconds(), tol);
}
