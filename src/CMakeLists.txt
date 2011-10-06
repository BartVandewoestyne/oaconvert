set(airspace_SRCS
    Airspace.cpp
    Arc.cpp
    Circle.cpp
    Coordinate.cpp
    CurvedPolygon.cpp
    latitude.cpp
    latlon.cpp
    LinearSegment.cpp
    longitude.cpp
    OutputWriter.cpp
    parser.cpp
    PolishState.cpp
    stringutils.cpp
)

add_library(airspace SHARED ${airspace_SRCS})

set(oa2pm_SRCS
    oa2pm.cpp
)
add_executable(oa2pm ${oa2pm_SRCS})
target_link_libraries(oa2pm airspace)
#target_link_libraries(oa2pm boost_regex)
target_link_libraries(oa2pm boost_regex-mt)
