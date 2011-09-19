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
{
  // See section 4.2.4.2 in http://cgpsmapper.com/download/cGPSmapper-UsrMan-v02.1.pdf
  cout << "[POLYGON]" << endl;
  cout << "Type=0x0a" << endl; // use same as oa2gm source code, figure out later why...
  cout << "Data0=" << endl;
  // TODO: loop over p.coords and plot all coordinates in this polygon.
  cout << "[END]" << endl;
}

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
