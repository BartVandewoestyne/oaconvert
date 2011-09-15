include_directories("../src")

set(MainTest_SRCS
    HeaderTest.cpp
    LatLonTest.cpp
    MainTester.cpp
    ParserTest.cpp
    AirSpaceTest.cpp
)

add_executable(MainTest ${MainTest_SRCS})
target_link_libraries(MainTest airspace)
target_link_libraries(MainTest boost_regex)
target_link_libraries(MainTest cppunit)
