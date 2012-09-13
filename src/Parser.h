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

#include <boost/regex.hpp>
#include <list>
#include <map>
#include <string>

#include "Airspace.h"
#include "Coordinate.h"
#include "OutputWriter.h"

class Arc;
class Coordinate;
class CurvedPolygon;


class Parser
{
private:
    enum ERegex
    {
        REGEX_DDMMSS,
        REGEX_DDMM,
        REGEX_DD,
        REGEX_FL,
        REGEX_AGL,
        REGEX_AAL,
        REGEX_AMSL,
        REGEX_MSL,
        REGEX_SFC,
        REGEX_FT,
        REGEX_GND,
        REGEX_AIRSPACE_FLOOR,
        REGEX_UNLIMITED,
        REGEX_ASK,
        REGEX_COMMENT,
        REGEX_AIRSPACE_CLASS,
        REGEX_AC,
        REGEX_AN,
        REGEX_AH,
        REGEX_AL,
        REGEX_AT,
        REGEX_VX,
        REGEX_VD,
        REGEX_DP,
        REGEX_DA,
        REGEX_DB,
        REGEX_DB_COORDS,
        REGEX_DC
    };

private:
    typedef std::pair<ERegex,boost::regex> pairtype;

    OutputWriter _writer; // TODO: rename this with other naming convention.

    std::list<Airspace*> airspaces;

    char currentDirection;

    // The last read center point for an DA, DB or DC record.
    // TODO: this variable name is confusing... better name it something
    //       like currentArcCenter or so...
    // Since this private member can be null, we should probably make it
    // a pointer..., but then we also need a decent destructor, copy constructor
    // and assignment operator.
    Coordinate currentCoordinate;

    std::map<ERegex,boost::regex> regexMap;

    // To prevent clients from calling these, and to prevent compilers from
    // generating these, we only declare, but do not implement the copy
    // constructor and assignment operator.  See [Meyers 2005], Item 11, second
    // last paragraph.
    Parser(const Parser& p);
    Parser operator=(const Parser& p); // TODO: the output argument should be ref!

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
    std::string parseAirspaceClass(const std::string& clss) const;
    std::string parseFileExtension(const std::string& fileName) const;

    void setCurrentDirection(const char d);
    void setCurrentAirspace(const Airspace &s);
    void setCurrentCoordinate(const Coordinate &c);

    void initialize();
    void writeAirspaces();
    void finalize();

private:
    void initRegexMap();

};


inline Airspace* Parser::getCurrentAirspace()
{
    return airspaces.size() > 0 ? airspaces.back() : 0;
}

#endif /* PARSER_H */
