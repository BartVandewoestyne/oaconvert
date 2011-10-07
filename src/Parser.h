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

#ifndef PARSER_H
#define PARSER_H 

#include <list>
#include <string>
#include "Airspace.h"
#include "Coordinate.h"
#include "OutputWriter.h"

class Arc;
class Coordinate;
class CurvedPolygon;


class Parser {

  private:

    OutputWriter _writer;

    std::list<Airspace*> airspaces;

    char currentDirection;
    Coordinate currentCoordinate;
    CurvedPolygon *curved_polygon;

  public:

    Parser();
    Parser(const std::string& outfile);
    ~Parser();

    void handleLine(const std::string& s);

    char getCurrentDirection() const;
    Airspace* getCurrentAirspace();
    const Coordinate& getCurrentCoordinate() const;

    Coordinate parseCoordinate(const std::string& s) const;
    double parseAltitude(const std::string& s) const;

    void setCurrentDirection(const char d);
    void setCurrentAirspace(const Airspace &s);
    void setCurrentCoordinate(const Coordinate &c);

    /** Initialize this parser to start parsing the contents of the input file.
     *  In practice, this includes the writing of the header to the desired output stream.
     */
    void initialize();

    void finalize();

  private:
    void addLinearSegment( const Coordinate& point );
    void addArc( const Arc& arc );

};


inline Airspace* Parser::getCurrentAirspace()
{
  return airspaces.size() > 0 ? airspaces.back() : 0;
}

#endif /* PARSER_H */
