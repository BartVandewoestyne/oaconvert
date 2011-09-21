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
  if (p.getNbPoints() > 0) {
    outputStream << "Polygon:" << endl;
    for (unsigned int i = 0; i< p.coords.size(); ++i)
    {
      outputStream << "  " << p.coords[i] << endl;
    }
  }
  return outputStream;
}
