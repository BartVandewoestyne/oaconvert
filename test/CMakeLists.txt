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

find_package(Boost REQUIRED regex)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(MainTest ${Boost_REGEX_LIBRARY})
  target_link_libraries(MainTest cppunit)
  target_link_libraries(MainTest airspace)
endif()
