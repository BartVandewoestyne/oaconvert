set(airspace_SRCS
    Airspace.cpp
    Arc.cpp
    Circle.cpp
    Coordinate.cpp
    CurvedPolygon.cpp
    Label.cpp
    Latitude.cpp
    LatLon.cpp
    Longitude.cpp
    OutputWriter.cpp
    Parser.cpp
    Point.cpp
    PolishState.cpp
    GPXState.cpp
    KMLState.cpp
    StringUtils.cpp
)

set(oaconvert_SRCS
    oaconvert.cpp
)

add_library(airspace SHARED ${airspace_SRCS})
add_executable(oaconvert ${oaconvert_SRCS})

# See `cmake --help-module FindBoost` for more info
# about the things below.
# See also
# http://www.cpprocks.com/using-cmake-to-build-a-cross-platform-project-with-a-boost-dependency/
find_package(Boost REQUIRED regex)
#message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
#message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
#message(status "** Boost Libraries: ${Boost_LIBRARIES}")
if (Boost_FOUND)
   include_directories(${Boost_INCLUDE_DIRS})
   target_link_libraries(airspace ${Boost_REGEX_LIBRARY})
   target_link_libraries(oaconvert airspace)
endif()
