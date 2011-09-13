#include <iostream>
#include <fstream>
#include <unistd.h>
#include "latitude.h"
#include "header.h"
#include "stringutils.h"
#include "airspace.h"
using namespace std;

int main (int argc, char* argv[])
{

  if (argc < 2)
  {
    printf("Usage:\n");
    printf("%s [-o polish_file.mp] open_air_file.txt\n", argv[0]);
    exit(1);
  }

  int index;
  int opt;

  while ( (opt = getopt(argc, argv, "o:")) != -1 ) {
    switch (opt) {
      case 'o':
        printf("Option argument: %s\n", optarg);
        break;
      default: /* '?' */
        fprintf(stderr, "Usage: %s [-o file.txt] file.air\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  if (optind >= argc) {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_FAILURE);
  }
  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;

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
