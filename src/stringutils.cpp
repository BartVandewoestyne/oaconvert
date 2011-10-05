/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.
  
  This file is part of oaconvert.
  
  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

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
