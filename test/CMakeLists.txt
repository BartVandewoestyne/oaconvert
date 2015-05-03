include_directories("../src")

set(MainTest_SRCS
    ArcTest.cpp
    LatLonTest.cpp
    LatitudeTest.cpp
    LongitudeTest.cpp
    CoordinateTest.cpp
    MainTester.cpp
    ParserTest.cpp
    AirspaceTest.cpp
)

add_executable(MainTest ${MainTest_SRCS})
target_link_libraries(MainTest cppunit airspace)
