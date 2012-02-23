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

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Weffc++ -DDEBUG")


# Set this according to whatever works for you...
# TODO: can we let cmake automatically determine the name of the
#       boost library???
set(BOOST_LIBNAME "boost_regex")
#set(BOOST_LIBNAME "boost_regex-mt")

target_link_libraries(airspace ${BOOST_LIBNAME})
target_link_libraries(oaconvert airspace)
