cmake_minimum_required(VERSION 2.8.6)

project(gf CXX)

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
	SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror ${CMAKE_CXX_FLAGS}")
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
 

#GTEST and GMOCK build
SET(BUILD_GTEST ON CACHE BOOL "Use some expat option")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest)

# include directory
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googlemock/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googletest/include
)

#inclue sources
include(cmake/gf.cmake)
include(cmake/gf_test.cmake)

#add library
add_library(gf ${gf_SOURCES})

# test
enable_testing()

add_executable(gf_test ${gf_test_SOURCES})
target_link_libraries(gf_test gf)
target_link_libraries(gf_test gmock)
target_link_libraries(gf_test gtest)
add_test(gf_test gf_test)

# benchmarks
IF(GF_BUILD_BENCHMARKS)
	ADD_SUBDIRECTORY(benchmarks)
ENDIF()

# benchmarks
IF(GF_BUILD_EXAMPLES)
	ADD_SUBDIRECTORY(examples)
ENDIF()
