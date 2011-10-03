#include <iostream>
#include <fstream>
//#include <unistd.h>
#include <getopt.h>
#include <boost/regex.hpp> 

#include "latitude.h"
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

  int write_to_stdout = 0;
  std::string filename;

  static struct option long_options[] =
  {
  /* These options set a flag. */
    { "stdout", no_argument, &write_to_stdout, 1},
    { "out", required_argument, 0, 'o' },
    { 0, 0, 0, 0 }
  };


  int opt;
  int option_index;


  while ( (opt = getopt_long(argc, argv, "o:", long_options, &option_index)) != -1 ) {

    switch (opt) {
      case 0:
        if (long_options[option_index].flag != 0)
          break;
        printf ("option %s", long_options[option_index].name);
        if (optarg)
          printf (" with arg %s", optarg);
        printf ("\n");
        if( strcmp(long_options[option_index].name, "out") == 0 )
          {
          filename = optarg;
          }
        break;

      case 'o':
        printf("Option argument: %s\n", optarg);
        filename = optarg;
        break;

      default: /* '?' */
        fprintf(stderr, "Usage: %s [-o|--out file.txt] [--stdout] file.air\n", argv[0]);
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

	// Setup the parser
  Parser *p;

  if( ! write_to_stdout )
  {
    if( filename == "" )
    {
      filename = "output.mp";
    }
    p = new Parser( filename );
  }
  else
  {
    p = new Parser();
  }

  // Start reading the input file.
  std::string infile(argv[1]);
  cout << "Processing file: " << infile << endl;
  string line;
  ifstream inStream;
  inStream.open(infile.c_str());
  if (inStream.is_open())
  {
    // Writer the header.
    p->initialize();

    while ( inStream.good() )
    {
      getline(inStream, line);
      p->handleLine(line);
    }

    // Make sure we also write the last airspace in the file + included the footer.
    p->finalize();

    inStream.close();
  }
  else cout << "Unable to open file!\n";

  // cleanup
  delete p;

  return 0;
}
