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
    int currentDirection;
    std::ostream out;

  public:
    Parser();
    Parser(std::ostream& stream);

    Coordinate getCoordinate(const std::string& s) const;
    void handleLine(const std::string& s);
    int getCurrentDirection() const;
    AirSpace& getCurrentAirSpace();
    const Coordinate& getCurrentCoordinate() const;
    void setCurrentAirspace(const AirSpace &s);
    void setCurrentCoordinate(const Coordinate &c);

};

#endif /* PARSER_H */
