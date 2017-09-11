LIST (APPEND benchmarks_PROGRAMS
    benchmark_galois_field_operator.cc
    benchmark_sequence_sobol.cc
)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/submodule/benchmark/include
)

FOREACH (source_file ${benchmarks_PROGRAMS})
    GET_FILENAME_COMPONENT (source_file_we ${source_file} NAME_WE)
    ADD_EXECUTABLE (
        ${source_file_we}
        ${source_file}
    )
    TARGET_LINK_LIBRARIES (${source_file_we}
        # gns
        benchmark
        gns
    )
    ADD_TEST (${source_file_we} ${source_file_we})
    IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        SET (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
        SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter ${CMAKE_CXX_FLAGS}")
        SET (CMAKE_CXX_FLAGS "-g -O3 ${CMAKE_CXX_FLAGS}")
        SET_PROPERTY (TARGET ${source_file_we} APPEND_STRING PROPERTY COMPILE_FLAGS "${CMAKE_CXX_FLAGS}")
    ENDIF ()
    IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # If profiling with gprof is on
        IF(GNS_BUILD_WITH_PROFILE)
            SET (CMAKE_CXX_FLAGS "-pg ${CMAKE_CXX_FLAGS}")
            SET (CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")
        ENDIF()
    ENDIF ()
    IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        SET_PROPERTY (TARGET ${source_file_we} APPEND_STRING PROPERTY COMPILE_FLAGS " -Wno-mismatched-tags")
    ENDIF ()
ENDFOREACH ()
