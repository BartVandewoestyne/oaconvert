#include <iostream>
#include <fstream>
#include "latitude.h"
#include "header.h"
#include "stringutils.h"
#include "airspace.h"
using namespace std;

int main (int argc, char* argv[])
{

  ifstream inStream;
  string line;

  //Latitude l(50, 46, 43);
  //cout << "l = " << l.getAngle() << "\n";

  Header h;
  h.writeHeader();

  inStream.open(argv[1]);
  if (inStream.is_open())
  {
    while ( inStream.good() )
    {
      StringUtils s;

      getline(inStream, line);
      s.trim(line);

      string token="AC";
      if ( s.startsWith(line, token) )
      {
        AirSpace currentSpace(token);

        getline(inStream, line);
        while ( !s.startsWith(line, token) ) {
          currentSpace.handleLine(line);
          getline(inStream, line);
        }

        currentSpace.print();

      }

    }
    inStream.close();
  }
  else cout << "Unable to open file!\n";

  return 0;
}
