#ifndef PARSER_H
#define PARSER_H 

#include <list>
#include <string>

#include "airspace.h"
#include "Coordinate.h"
#include "OutputWriter.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
//////////////////////////////////////////////////////////////////////////////////////////
class CurvedPolygon;

//////////////////////////////////////////////////////////////////////////////////////////
// Class Parser
//////////////////////////////////////////////////////////////////////////////////////////
class Parser {

  private:
    OutputWriter _writer;

    std::list<AirSpace*> airspaces;

    // Helper variables
    Coordinate currentCoordinate;
    char currentDirection;
    CurvedPolygon *curved_polygon;

  public:
    Parser();
    Parser(const std::string& outfile);
    ~Parser();

    void handleLine(const std::string& s);

    AirSpace* getCurrentAirSpace();
    const Coordinate& getCurrentCoordinate() const;
    char getCurrentDirection() const;
    Coordinate getCoordinate(const std::string& s) const;

    void setCurrentAirspace(const AirSpace &s);
    void setCurrentCoordinate(const Coordinate &c);
    void setCurrentDirection(const char d);

    /** Initialize this parser to start parsing the contents of the input file.
     *  In practice, this includes the writing of the header to the desired output stream.
     */
    void initialize();

    /** Initialize this parser to start parsing the contents of the input file.
     *  In practice, this includes the writing of the footer to the desired output stream.
     */
    void finalize();

};

//////////////////////////////////////////////////////////////////////////////////////////
// Inline functions
//////////////////////////////////////////////////////////////////////////////////////////

inline AirSpace* Parser::getCurrentAirSpace()
{
  return airspaces.size() > 0 ? airspaces.back() : 0;
}

#endif /* PARSER_H */
