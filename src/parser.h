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

    AirSpace& getCurrentAirSpace();
    const Coordinate& getCurrentCoordinate() const;
    char getCurrentDirection() const;
    Coordinate getCoordinate(const std::string& s) const;

    void setCurrentAirspace(const AirSpace &s);
    void setCurrentCoordinate(const Coordinate &c);
    void setCurrentDirection(const char d);

    void finalize();

  private:
    void init();
};

//////////////////////////////////////////////////////////////////////////////////////////
// Inline functions
//////////////////////////////////////////////////////////////////////////////////////////

inline AirSpace& Parser::getCurrentAirSpace()
{
  return *(airspaces.back());
}

#endif /* PARSER_H */
