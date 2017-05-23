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

# include directory
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/submodule
	${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googlemock/include
	${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googletest/include
)
 
#inclue sources
INCLUDE(cmake/gf.cmake)

#add library
ADD_LIBRARY(gf ${gf_SOURCES})

# test
IF(GF_BUILD_TEST OR GF_BUILD_TEST_MEMORYCHECK)
	#GTEST and GMOCK build
	SET(BUILD_GTEST ON CACHE BOOL "Use some expat option")
	ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest)

	INCLUDE(cmake/gf_test.cmake)
	ENABLE_TESTING()

	ADD_EXECUTABLE(gf_test ${gf_test_SOURCES})
	TARGET_LINK_LIBRARIES(gf_test gf)
	TARGET_LINK_LIBRARIES(gf_test gmock)
	TARGET_LINK_LIBRARIES(gf_test gtest)
	ADD_TEST(gf_test gf_test)

	# memcheck
	IF(GF_BUILD_TEST_MEMORYCHECK)
		FIND_PROGRAM(MEMORYCHECK_COMMAND NAMES valgrind)
		SET(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=definite,possible --error-exitcode=1")
		SET(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/ci/valgrind_suppression.supp" )
	ENDIF()
ENDIF()

# benchmarks
IF(GF_BUILD_BENCHMARKS)
	ADD_SUBDIRECTORY(benchmarks)
ENDIF()

# benchmarks
IF(GF_BUILD_EXAMPLES)
	ADD_SUBDIRECTORY(examples)
ENDIF()
