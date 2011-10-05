include_directories("../src")

set(MainTest_SRCS
    LatLonTest.cpp
    LatitudeTest.cpp
    LongitudeTest.cpp
    CoordinateTest.cpp
    MainTester.cpp
    ParserTest.cpp
    AirspaceTest.cpp
)

add_executable(MainTest ${MainTest_SRCS})
target_link_libraries(MainTest airspace)
target_link_libraries(MainTest boost_regex)
target_link_libraries(MainTest cppunit)
