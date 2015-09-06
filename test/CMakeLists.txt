if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # When building with Clang, we need to compile cppunit ourselves or we get
    # linking errors...
    include(ExternalProject)
    ExternalProject_Add(
        cppunit_external
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        PREFIX ${CMAKE_BINARY_DIR}/cppunit
        URL http://dev-www.libreoffice.org/src/cppunit-1.13.2.tar.gz
        URL_MD5 d1c6bdd5a76c66d2c38331e2d287bc01
        CONFIGURE_COMMAND sh -c "<SOURCE_DIR>/configure --prefix=<INSTALL_DIR> CXX=${CMAKE_CXX_COMPILER} CXXFLAGS='${CMAKE_CXX_FLAGS}' ${PACKAGE_COMPILER_FLAGS} ${PACKAGE_CONFIGURE_FLAGS}"
#        GIT_REPOSITORY git://anongit.freedesktop.org/git/libreoffice/cppunit/
#        GIT_TAG cppunit-1.13.2
#        CONFIGURE_COMMAND sh -c "<SOURCE_DIR>/autogen.sh && <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> CXX=${CMAKE_CXX_COMPILER} CXXFLAGS='${CMAKE_CXX_FLAGS}' ${PACKAGE_COMPILER_FLAGS} ${PACKAGE_CONFIGURE_FLAGS}"
        BUILD_IN_SOURCE 1
        BUILD_COMMAND make
        INSTALL_COMMAND make install
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        )

    ExternalProject_Get_Property(cppunit_external install_dir)
    add_library(cppunit STATIC IMPORTED)
    set_property(TARGET cppunit PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libcppunit.a)
endif()

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

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_dependencies(MainTest cppunit_external)
endif()

target_link_libraries(MainTest cppunit airspace)

# vim: expandtab
