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

#include <iostream>
#include <fstream>
#include <getopt.h>
#include <boost/regex.hpp> 

#include "Airspace.h"
#include "Latitude.h"
#include "Parser.h"
#include "StringUtils.h"

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
  std::string outfilename;

  static struct option long_options[] =
  {
    { "stdout",       no_argument, &write_to_stdout,  1 },
    {    "out", required_argument,                0, 'o'},
    {        0,                 0,                0,  0 }
  };


  int opt;
  int option_index;

  while ( (opt = getopt_long(argc, argv, "o:", long_options, &option_index)) != -1 ) {

    switch (opt) {

      case 0:
        if (long_options[option_index].flag != 0)
          {
            break;
          }
        printf ("option %s", long_options[option_index].name);
        if (optarg)
          printf (" with arg %s", optarg);
        printf ("\n");

        if ( strcmp(long_options[option_index].name, "out") == 0 )
          {
          outfilename = optarg;
          }
        break;

      case 'o':
        printf("Option argument: %s\n", optarg);
        outfilename = optarg;
        break;

      default: /* '?' */
        fprintf(stderr, "Usage: %s [-o|--out polish_file.mp] [--stdout] open_air_file.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  // At least one non-option argument, i.e., the input file.
  if (optind >= argc) {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_FAILURE);
  }

  // Read filename of the input file.
  std::string infilename( argv[optind] );


  // Setup the parser
  Parser *p;

  if( ! write_to_stdout )
  {
    if( outfilename == "" )
    {
      outfilename = "output.mp";
    }
    p = new Parser( outfilename );
  }
  else
  {
    p = new Parser();
  }

  // Start reading the input file.
  std::string infile(infilename);
  cout << "Processing file: " << infile << endl;
  cout << " +-> outputfile: " << ( strcmp(outfilename.c_str(),"") ? outfilename : "stdout" ) << endl;
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
