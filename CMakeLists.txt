cmake_minimum_required(VERSION 2.8.6)

project(gns CXX)

# Make sure we can import out CMake functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Import our CMake modules
include(AddCXXCompilerFlag)

#compiler option with accordance to compiler
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter ${CMAKE_CXX_FLAGS}")
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
ADD_LIBRARY(gns ${gns_SOURCES})

# test
IF(GNS_BUILD_TEST OR GNS_BUILD_TEST_MEMORYCHECK)
#GTEST and GMOCK build
    SET(BUILD_GTEST ON CACHE BOOL "Use some expat option")
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest)

    INCLUDE(cmake/gns_test.cmake)
    ENABLE_TESTING()

    ADD_EXECUTABLE(gns_test ${gns_test_SOURCES})
    TARGET_LINK_LIBRARIES(gns_test gns)
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

# if you enable an option by `-DCMAKE_BUILD_TYPE=Coverage`,
# add the coverage command(s)
if (${CMAKE_BUILD_TYPE} MATCHES "Coverage")
  # Coverage build type
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C++ compiler during coverage builds."
    FORCE)
  set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Flags used for linking binaries during coverage builds."
    FORCE)
  set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the shared libraries linker during coverage builds."
    FORCE)
  mark_as_advanced(
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_EXE_LINKER_FLAGS_COVERAGE
    CMAKE_SHARED_LINKER_FLAGS_COVERAGE)
  set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Coverage."
    FORCE)

  add_cxx_compiler_flag(--coverage COVERAGE)
  find_program(GCOV gcov)
  find_program(LCOV lcov)
  find_program(GENHTML genhtml)
  find_program(CTEST ctest)
  if (GCOV AND LCOV AND GENHTML AND CTEST AND HAVE_CXX_FLAG_COVERAGE)
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/lcov/index.html
      COMMAND ${LCOV} -q -z -d .
      COMMAND ${LCOV} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o before.lcov -i
      COMMAND ${CTEST} --force-new-ctest-process
      COMMAND ${LCOV} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o after.lcov
      COMMAND ${LCOV} -q -a before.lcov -a after.lcov --output-file final.lcov
      COMMAND ${LCOV} -q -r final.lcov "'${CMAKE_SOURCE_DIR}/test/*'" -o final.lcov
      COMMAND ${GENHTML} final.lcov -o lcov --demangle-cpp --sort -p "${CMAKE_BINARY_DIR}" -t gns
      DEPENDS gns_test
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running LCOV"
    )
    add_custom_target(coverage
      DEPENDS ${CMAKE_BINARY_DIR}/lcov/index.html
      COMMENT "LCOV report at lcov/index.html"
    )
    message(STATUS "Coverage command added")
  else()
    if (HAVE_CXX_FLAG_COVERAGE)
      set(CXX_FLAG_COVERAGE_MESSAGE supported)
    else()
      set(CXX_FLAG_COVERAGE_MESSAGE unavailable)
    endif()
    message(WARNING
      "Coverage not available:\n"
      "  gcov: ${GCOV}\n"
      "  lcov: ${LCOV}\n"
      "  genhtml: ${GENHTML}\n"
      "  ctest: ${CTEST}\n"
      "  --coverage flag: ${CXX_FLAG_COVERAGE_MESSAGE}")
  endif()
endif()

# benchmarks
IF(GNS_BUILD_BENCHMARKS)
    # turn off test of google/benchmark
    option(BENCHMARK_ENABLE_TESTING "tests in google/benchmark off" OFF)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/submodule/benchmark)
    ADD_SUBDIRECTORY(benchmarks)
ENDIF()

# benchmarks
IF(GNS_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF()
