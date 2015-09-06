# Note:
#   If you want to see the actual compile-commands, run
#
#     make VERBOSE=1

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 2.6)

project(oaconvert CXX)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wabi -Wmissing-declarations -Wconversion -Wcast-align -Wredundant-decls -Werror -pedantic")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(GCC_MIN_VER "4.9")
    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "${GCC_MIN_VER}")
        message(FATAL_ERROR "GCC version should be at least ${GCC_MIN_VER}!")
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

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

# vim: expandtab
