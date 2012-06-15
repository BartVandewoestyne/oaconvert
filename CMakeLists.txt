# Note:
#   If you want to see the actual compile-commands, run
#
#     make VERBOSE=1

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 2.6)

project(oaconvert)

add_definitions(-DDEBUG)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Weffc++ -pedantic")

add_subdirectory(src)
add_subdirectory(test)

add_custom_target(reformat
                  astyle --options=astyle_options src/*.cpp src/*.h
                  COMMENT "Beautifying CPP source files"
                  VERBATIM)

# TODO: this is not working yet, fix it.  The problem is
#       the quotes around "*.orig" when typing `make origclean`.
#add_custom_target(origclean
#                  rm -f *.orig
#                  COMMENT "Removing astyle backup files"
#                  WORKING_DIRECTORY src
#                  VERBATIM)
