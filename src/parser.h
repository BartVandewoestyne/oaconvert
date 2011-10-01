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
class Circle;
class CurvedPolygon;
class Region;

//////////////////////////////////////////////////////////////////////////////////////////
// Class Parser
//////////////////////////////////////////////////////////////////////////////////////////
class Parser {

  private:
    OutputWriter _writer;
    Coordinate currentCoordinate;
    char currentDirection;

    std::list<AirSpace*> airspaces;

    // Helper variables
    Circle* circle;
    CurvedPolygon* curved_polygon;
    Region* current_region; // Points to one of above circle of curved_polygon.

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
