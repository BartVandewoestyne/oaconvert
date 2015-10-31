if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR 
        (NOT CPPUNIT AND NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC"))
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
        LOG_INSTALL ON
        )

    ExternalProject_Get_Property(cppunit_external install_dir)
    add_library(cppunit STATIC IMPORTED)
    set_property(TARGET cppunit PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libcppunit.a)
    # Make sure to put SYSTEM in the following command! It will make the
    # compiler consider the cppunit headers system headers, which makes them
    # immune against certain warnings. See http://stackoverflow.com/questions/3371127/use-isystem-instead-of-i-with-cmake
    include_directories(SYSTEM "${install_dir}/include")

    # Flag that cppunit will be available.
    set(CPPUNIT True)
endif()

if(CPPUNIT)
    message(STATUS "Enabling unit testing")

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

    target_include_directories(MainTest PRIVATE "../src")

    if(TARGET cppunit_external)
        add_dependencies(MainTest cppunit_external)
    endif()

    target_link_libraries(MainTest cppunit airspace)

    add_test(airspace MainTest)

else()
  message(WARNING "Cppunit was not found and we could not compile it "
                  "automatically ourselves. Unit testing will be disabled.")
endif()

# vim: expandtab
