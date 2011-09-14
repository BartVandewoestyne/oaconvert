set(airspace_SRCS
    airspace.cpp
    coordinate.cpp
    header.cpp
    latlon.cpp
    latitude.cpp
    longitude.cpp
    parser.cpp
    point.cpp
    restricted.cpp
    stringutils.cpp
)

add_library(airspace SHARED ${airspace_SRCS})

set(oa2pm_SRCS
    oa2pm.cpp
)
add_executable(oa2pm ${oa2pm_SRCS})
target_link_libraries(oa2pm airspace)
target_link_libraries(oa2pm boost_regex )
