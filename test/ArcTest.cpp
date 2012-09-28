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

#include "ArcTest.h"
#include "Arc.h"
#include "Coordinate.h"
#include "Point.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( ArcTest );

void
ArcTest::setUp()
{}


void
ArcTest::tearDown()
{}


void
ArcTest::testCoutOperator()
{
  Coordinate centerCoord(Latitude(50,  3, 59, 'N'), Longitude(5, 42, 53, 'W'));
  Point centerPoint(centerCoord);

  Arc arc(centerPoint, 2.5, 100, 200, '+');

  cout << endl << arc << endl;
}
