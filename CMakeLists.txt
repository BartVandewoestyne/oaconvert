# If you want to see the actual commands, run
#
#   make VERBOSE=1

cmake_minimum_required(VERSION 2.8)

project(oaconvert)

add_definitions(-Wall -g)

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
