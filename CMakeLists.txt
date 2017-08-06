cmake_minimum_required(VERSION 2.8.6)

project(gns CXX)

#compiler option with accordance to compiler
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror ${CMAKE_CXX_FLAGS}")
    # for debug
    SET (CMAKE_CXX_FLAGS_DEBUG, "-g ${CMAKE_CXX_FLAGS_DEBUG}")
    # for release
    SET (CMAKE_CXX_FLAGS_RELEASE "-O2 ${CMAKE_CXX_FLAGS_RELEASE}")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter ${CMAKE_CXX_FLAGS}")
    # for debug
    SET (CMAKE_CXX_FLAGS_DEBUG, "-g ${CMAKE_CXX_FLAGS_DEBUG}")
    ## for google perftools on Mac
    SET (CMAKE_CXX_FLAGS_DEBUG, "-Wl,-no_pie  ${CMAKE_CXX_FLAGS_DEBUG}")
    # for release
    SET (CMAKE_CXX_FLAGS_RELEASE "-O2 ${CMAKE_CXX_FLAGS_RELEASE}")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    IF (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19)
        MESSAGE ( FATAL_ERROR "MSVC doesn't support C++11.")
    ENDIF ()
ENDIF ()

# include directory
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googlemock/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googletest/include
)

#inclue sources
INCLUDE(cmake/gns.cmake)

#add library
# ADD_LIBRARY(gns ${gns_SOURCES})

# test
IF(GNS_BUILD_TEST OR GNS_BUILD_TEST_MEMORYCHECK)
#GTEST and GMOCK build
    SET(BUILD_GTEST ON CACHE BOOL "Use some expat option")
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest)

    INCLUDE(cmake/gns_test.cmake)
    ENABLE_TESTING()

    ADD_EXECUTABLE(gns_test ${gns_test_SOURCES})
    # TARGET_LINK_LIBRARIES(gns_test gns)
    TARGET_LINK_LIBRARIES(gns_test gmock)
    TARGET_LINK_LIBRARIES(gns_test gtest)
    ADD_TEST(gns_test gns_test)

    # memcheck
    IF(GNS_BUILD_TEST_MEMORYCHECK)
        SET(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=definite,possible --error-exitcode=1")
        SET(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/ci/valgrind_suppression.supp" )
        FIND_PROGRAM(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
        # Dart must be at the end of configuration
        INCLUDE(Dart)
    ENDIF()
ENDIF()

# benchmarks
IF(GNS_BUILD_BENCHMARKS)
    set(BENCHMARK_ENABLE_TESTING OFF)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/submodule/benchmark)
    ADD_SUBDIRECTORY(benchmarks)
ENDIF()

# benchmarks
IF(GNS_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF()
