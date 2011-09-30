#ifndef PARSER_H
#define PARSER_H 

#include <string>

#include "coordinate.h"
#include "airspace.h"
#include "OutputWriter.h"

class Parser {

  private:
    OutputWriter _writer;
    AirSpace currentAirSpace;
    Coordinate currentCoordinate;
    char currentDirection;

  public:
    Parser();
    Parser(std::ostream& stream);

    void handleLine(const std::string& s);

    AirSpace& getCurrentAirSpace();
    const Coordinate& getCurrentCoordinate() const;
    char getCurrentDirection() const;
    Coordinate getCoordinate(const std::string& s) const;

    void setCurrentAirspace(const AirSpace &s);
    void setCurrentCoordinate(const Coordinate &c);
    void setCurrentDirection(const char d);

};

#endif /* PARSER_H */
