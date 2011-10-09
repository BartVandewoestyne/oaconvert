set(airspace_SRCS
    Airspace.cpp
    Arc.cpp
    Circle.cpp
    Coordinate.cpp
    CurvedPolygon.cpp
    Label.cpp
    Latitude.cpp
    LatLon.cpp
    LinearSegment.cpp
    Longitude.cpp
    OutputWriter.cpp
    Parser.cpp
    PolishState.cpp
    GPXState.cpp
    StringUtils.cpp
)

add_library(airspace SHARED ${airspace_SRCS})

set(oaconvert_SRCS
    oaconvert.cpp
)

#set(CMAKE_CXX_FLAGS "-g -Wall -DDEBUG")

add_executable(oaconvert ${oaconvert_SRCS})
target_link_libraries(oaconvert airspace)
#target_link_libraries(oaconvert boost_regex)
target_link_libraries(oaconvert boost_regex-mt)
