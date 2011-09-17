// vim: expandtab
#ifndef PARSER_H
#define PARSER_H 

#include <string>

#include "coordinate.h"
#include "airspace.h"

class Parser {

  private:
    AirSpace currentAirSpace;
    Coordinate currentCoordinate;
    int currentDirection;
    std::ostream out;

  public:
    Parser();
    Parser(std::ostream& stream);

    Coordinate getCoordinate(std::string s);
    void handleLine(string s);
    int getCurrentDirection();
    AirSpace& getCurrentAirSpace();
    Coordinate& getCurrentCoordinate();
    void setCurrentAirspace(AirSpace s);
    void setCurrentCoordinate(Coordinate c);

};

#endif /* PARSER_H */
