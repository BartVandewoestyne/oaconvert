# Note:
#   If you want to see the actual compile-commands, run
#
#     make VERBOSE=1

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 2.6)

project(oaconvert CXX)

find_program(ASTYLE astyle)
find_library(CPPUNIT LIBRARY
    NAMES cppunit)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wabi -Wmissing-declarations -Wconversion -Wcast-align -Wredundant-decls -pedantic")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(GCC_MIN_VER "4.7")
    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "${GCC_MIN_VER}")
        message(FATAL_ERROR "GCC version should be at least ${GCC_MIN_VER}!")
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_subdirectory(src)

add_subdirectory(test)

if(ASTYLE)
    add_custom_target(reformat
                      ${ASTYLE} --options=astyle_options src/*.cpp src/*.h 
                      COMMENT "Beautifying CPP source files"
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      VERBATIM)

    add_custom_target(origclean
                      rm -f *.orig
                      COMMENT "Removing astyle backup files"
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
else()
    message(WARNING "Could not find astyle. To be able to beautify the source code, install it from http://astyle.sourceforge.net/.")
endif()

# vim: expandtab
