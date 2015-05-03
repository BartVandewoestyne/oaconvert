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
target_link_libraries(oaconvert airspace)
