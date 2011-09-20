#include <iostream>
#include <fstream>
#include <unistd.h>
#include <boost/regex.hpp> 
#include "latitude.h"
#include "header.h"
#include "stringutils.h"
#include "parser.h"
#include "airspace.h"

using namespace std;
using namespace boost;

int main (int argc, char* argv[])
{

  if (argc < 2)
  {
    printf("Usage:\n");
    printf("%s [-o polish_file.mp] open_air_file.txt\n", argv[0]);
    exit(1);
  }

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

  //int index;
  //for (index = optind; index < argc; index++) {
  //  printf ("Non-option argument %s\n", argv[index]);
  //}

	// Make output to file or to stdout controllable.
	streambuf *buf;
	ofstream of;
	bool write_to_file = false;
	string outfilename( "output.mp" );
	if( write_to_file )
	{
		of.open( outfilename.c_str() );
		buf = of.rdbuf();
	}
	else
	{
		buf = cout.rdbuf();
	}
	ostream out( buf );

	// Setup 
  Parser p( out );
  OutputWriter w(out);
  w.writeHeader();

  string line;
  ifstream inStream;
  inStream.open(argv[1]);
  if (inStream.is_open())
  {
    while ( inStream.good() )
    {
      getline(inStream, line);
      p.handleLine(line);
    }
    inStream.close();
  }
  else cout << "Unable to open file!\n";

  return 0;
}
