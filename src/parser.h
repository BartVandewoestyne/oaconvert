#ifndef PARSER_H
#define PARSER_H 

#include <string>
using namespace std;

#include "coordinate.h"

class Parser {

  public:
    Coordinate getCoordinate(std::string s);

};

#endif /* PARSER_H */
