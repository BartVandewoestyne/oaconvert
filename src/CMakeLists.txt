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
    StringUtils.cpp
)

set(oaconvert_SRCS
    oaconvert.cpp
)

add_library(airspace SHARED ${airspace_SRCS})
add_executable(oaconvert ${oaconvert_SRCS})

#set(CMAKE_CXX_FLAGS "-g -Wall -DDEBUG")

target_link_libraries(airspace boost_regex-mt)
target_link_libraries(oaconvert airspace)
#target_link_libraries(oaconvert boost_regex)
#target_link_libraries(oaconvert ${Boost_LIBRARIES})

# This works on Linux, but not in cygwin.
target_link_libraries(oaconvert boost_regex-mt)
