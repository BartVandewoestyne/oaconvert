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
#include <string>

#include "Airspace.h"
#include "Latitude.h"
#include "Parser.h"

static std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += static_cast<char> (c);
        }
    }
}


int main (int argc, char* argv[])
{

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [-d|--debug level] [-o|--output polish_file.mp] open_air_file.txt" << std::endl;
        exit(EXIT_FAILURE);
    }

    // By default, if no output file is given, write to stdout.
    std::string outfilename;
    std::string infilename;

    auto getNextParameter = [argc, argv](int index) -> std::string
    {
        if(index >= argc)
        {
            std::cerr << "ERROR: invalid index '" << index << "'. There are only " << argc << " arguments." << std::endl;
        }
        if(index + 1 < argc)
        {
            return argv[index + 1];
        }
        else
        {
            std::cerr << "ERROR: Expected argument for " << argv[index] << "." << std::endl;
            exit(EXIT_FAILURE);
        }
    };

    for(int i = 1; i < argc; ++i)
    {
        std::string option = argv[i];

        if(option == "-u" || option == "--units")
        {
            auto units = getNextParameter(++i);
            if(units == "ft")
            {
                std::cout << "TODO: setting output display units to feet." << std::endl;
            }
            else if(units == "m")
            {
                std::cout << "TODO: setting output display units to meters." << std::endl;
            }
            else
            {
                std::cout << "ERROR: display units must be 'ft' (feet) or 'm' (meters)." << std::endl;
                return EXIT_FAILURE;
            }
        }

        else if(option == "-o" || option == "--output")
        {
            outfilename = getNextParameter(i++);
        }

        else if(option == "-d" || option == "--debug")
        {
            auto debuglevel = getNextParameter(i++);
            std::cout << "Requested debug level: " << debuglevel << std::endl;
            std::cout << "WARNING: Debug level output is not implemented yet!" << std::endl;
        }

        else if(option == "-h" || option == "--help")
        {
            std::cout << "TODO: implement help text." << std::endl;
            exit(EXIT_SUCCESS);
        }

        else if(option == "-v" || option == "--version")
        {
            std::cout << "oa2convert <some_version>" << std::endl;
            std::cout << "Copyright (C) 2011 Bart Vandewoestyne, Yves Frederix" << std::endl;
            std::cout << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << std::endl;
            std::cout << "This is free software: you are free to change and redistribute it." << std::endl;
            std::cout << "There is NO WARRANTY, to the extent permitted by law." << std::endl;
            exit(EXIT_SUCCESS);
        }

        else
        {
            if(!infilename.empty())
            {
                std::cerr << "WARNING: more than one input file given. Ignoring '" << option << "'..." << std::endl;
            }
            else
            {
                infilename = option;
            }
        }
    }

    if (infilename.empty())
    {
        std::cerr << "ERROR: you must provide an OpenAir file after your options!!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Setup the parser
    std::unique_ptr<Parser> p;

    if (outfilename.empty())
    {
        p = std::unique_ptr<Parser>(new Parser());
    }
    else
    {
        p = std::unique_ptr<Parser>(new Parser(outfilename));
        //cout << "INFO: output file has extension ." << p->parseFileExtension( outfilename ) << "." << endl;
    }

    // Read the input (OpenAir) file.
    std::string infile(infilename);
    std::string line;
    std::ifstream inStream;
    inStream.open(infile.c_str());
    if (inStream.is_open())
    {
        while ( inStream.good() )
        {
            safeGetline(inStream, line);
            p->handleLine(line);
        }

        inStream.close();
    }
    else
    {
        std::cerr << "ERROR: Unable to open file '" << infilename << "'!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Everything is parsed and stored, now write!
    p->writeAirspaces();

    return 0;
}
