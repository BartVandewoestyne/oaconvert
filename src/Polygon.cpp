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

#include "polygon.h"
#include <algorithm>

using namespace std;

Polygon::Polygon()
{
    //cout << "Polygon()" << endl;
}

void Polygon::add(const Coordinate &c)
{
    coords.push_back(c);
}

/**
 * Add the points of the specified polygon at the end of this polygon.
 * TODO: In fact, this is conceptual bullshit... we cannot add a closed polygon to
 *       another closed polygon without breaking them up and stitching things back together.
 *       This is a quick hack to make things work, but we should re-design things with Polygons
 *       and Polylines as separate concepts...
 */
void Polygon::add(const Polygon &p)
{
    for (int i=1; i<=p.getNbPoints(); i++)
    {
        add(p.getCoordinate(i));
    }
}

void Polygon::clear()
{
    coords.clear();
}

int Polygon::getNbPoints() const
{
    return coords.size();
}

const Coordinate& Polygon::getCoordinate(int i) const
{
    return coords[i-1];
}

ostream& operator <<(ostream& outputStream, const Polygon& p)
{
    if (p.getNbPoints() > 0)
    {
        outputStream << "Polygon:" << endl;
        for (unsigned int i = 0; i< p.coords.size(); ++i)
        {
            outputStream << "  " << p.coords[i] << endl;
        }
    }
    return outputStream;
}
