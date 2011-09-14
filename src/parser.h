#ifndef PARSER_H
#define PARSER_H 

#include <string>
using namespace std;

#include "coordinate.h"
#include "airspace.h"

class Parser {

  private:
    AirSpace currentAirSpace;

  public:
    Parser();
    Coordinate getCoordinate(std::string s);
    void handleLine(string s);
    AirSpace getCurrentAirSpace();
    void setCurrentAirspace(AirSpace s);

};

#endif /* PARSER_H */
