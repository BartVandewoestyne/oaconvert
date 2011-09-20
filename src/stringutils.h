#ifndef STRINGUTILS_H
#define STRINGUTILS_H 

#include <stdlib.h>
#include <string>

class StringUtils {

  public:
    bool startsWith(const std::string& src, const std::string& token) const;
    void trim(std::string& str);

};

#endif /* STRING_UTILS_H */
