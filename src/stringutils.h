#ifndef STRINGUTILS_H
#define STRINGUTILS_H 

#include <stdlib.h>
#include <string>
using namespace std;

class StringUtils {

  public:
    bool startsWith(std::string& src, std::string& token);
    void trim(std::string& str);

};

#endif /* STRING_UTILS_H */
