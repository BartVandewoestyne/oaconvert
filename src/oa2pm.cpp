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
#include <strings.h>
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
    fprintf(stderr,
            "Usage: %s [-d|--debug level] [-o|--output polish_file.mp] open_air_file.txt\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  // By default, if no output file is given, write to stdout.
  int write_to_stdout = 1;
  std::string outfilename;

  static struct option long_options[] =
  {
    {  "output", required_argument, 0, 'o'},
    {   "units", required_argument, 0, 'u'},
    {   "debug", optional_argument, 0, 'd'},
    {    "help",       no_argument, 0, 'h'},
    { "version",       no_argument, 0, 'v'},
    {         0,                 0, 0,  0 }
  };


  int opt;
  int option_index;

  while ( (opt = getopt_long(argc, argv, "d::u:o:hv", long_options, &option_index)) != -1 ) {

    switch (opt) {

      case 0:
        printf ("option %s", long_options[option_index].name);
        if (optarg)
          printf (" with arg %s", optarg);
        printf ("\n");
        break;

      case 'u':

        if (!strcasecmp(optarg, "ft")) // this is counterintuitive...
        {
          printf ("TODO: setting output display units to feet.\n");
        }
        else if (!strcasecmp(optarg, "m")) // this is counterintuitive...
        {
          printf ("TODO: setting output display units to meters.\n");
        }
        else
        {
          printf("ERROR: display units must be 'ft' (feet) or 'm' (meters).\n");
          exit(EXIT_FAILURE);
        }
        break;

      case 'o':
        outfilename = optarg;
        write_to_stdout = 0;
        break;

      case 'd':
        printf("Requested debug level: %s\n", optarg);
        printf("WARNING: Debug level output is not implemented yet!\n");
        break;

      case 'h':
        printf("TODO: implement help text.\n");
        exit(EXIT_SUCCESS);

      case 'v':
        printf("oa2convert <some_version>\n");
        printf("Copyright (C) 2011 Bart Vandewoestyne, Yves Frederix\n");
        printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n");
        printf("This is free software: you are free to change and redistribute it.\n");
        printf("There is NO WARRANTY, to the extent permitted by law.\n");
        exit(EXIT_SUCCESS);

      default: /* '?' */
        fprintf(stderr,
                "Usage: %s [-d|--debug level] [-o|--output polish_file.mp] open_air_file.txt\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

  }

  // At least one non-option argument, i.e., the input file.
  if (optind >= argc) {
    fprintf(stderr, "ERROR: you must provide an OpenAir file after your options!!!\n");
    exit(EXIT_FAILURE);
  }

  // Read filename of the input file.
  std::string infilename( argv[optind] );


  // Setup the parser
  Parser *p;

  if ( write_to_stdout )
  {
    p = new Parser();
  }
  else
  {
    p = new Parser( outfilename );
  }

  // Start reading the input file.
  std::string infile(infilename);
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
  else cerr << "ERROR: Unable to open file!\n";

  // cleanup
  delete p;

  return 0;
}
