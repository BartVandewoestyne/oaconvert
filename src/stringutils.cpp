#include <iostream>
#include "stringutils.h"

using namespace std;

bool StringUtils::startsWith(const string& src, const string& token) const
{
  return ( src.substr(0, token.length()) == token );

  // TODO: Check this solution:
  // strncmp(str, substr, strlen(substr))
  // which will return 0 if str starts with substr.
}

void StringUtils::trim(string& str)
{

  // Trim both leading and trailing spaces.
  size_t startpos = str.find_first_not_of(" \t"); // Find the first character position after excluding leading blank spaces
  size_t endpos = str.find_last_not_of(" \t");    // Find the first character position from reverse af
  
  // if all spaces or empty return an empty string
  if ( ( string::npos == startpos ) || ( string::npos == endpos) )
  {
    str = "";
  }
  else
  {
    str = str.substr( startpos, endpos-startpos+1 );
  }
  
  /*
  // Code for Trim Leading Spaces only
  size_t startpos = str.find_first_not_of(” \t”); // Find the first character position after excluding leading blank spaces
  if( string::npos != startpos )
  str = str.substr( startpos );
  */
  
  /*
  // Code for Trim trailing Spaces only
  size_t endpos = str.find_last_not_of(” \t”); // Find the first character position from reverse af
  if( string::npos != endpos )
  str = str.substr( 0, endpos+1 );
  */

}
