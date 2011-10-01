set(airspace_SRCS
    airspace.cpp
    Coordinate.cpp
    latlon.cpp
    latitude.cpp
    longitude.cpp
    parser.cpp
    Circle.cpp
    Arc.cpp
    CurvedPolygon.cpp
    LinearSegment.cpp
    restricted.cpp
    stringutils.cpp
    OutputState.cpp
    PolishState.cpp
    OutputWriter.cpp
)

add_library(airspace SHARED ${airspace_SRCS})

set(oa2pm_SRCS
    oa2pm.cpp
)
add_executable(oa2pm ${oa2pm_SRCS})
target_link_libraries(oa2pm airspace)
#target_link_libraries(oa2pm boost_regex)
target_link_libraries(oa2pm boost_regex-mt)
