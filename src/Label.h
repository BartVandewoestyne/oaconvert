#ifndef LABEL_H
#define LABEL_H 

#include <stdlib.h>

class Label {

  private:
    std::string text;
    Coordinate coord;

  public:
    std::string getText();
    Coordinate getCoordinate();

};

#endif /* LABEL_H */
