#include "polygon.h"
 
using namespace std;

Polygon::Polygon()
{}

void Polygon::add(const Coordinate &c)
{
  coords.push_back(c);
}

void Polygon::clear()
{
  coords.clear();
}

void Polygon::toPolish(ostream& outputStream) const
{}

int Polygon::getNbPoints() const
{
  return coords.size();
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
