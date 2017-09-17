LIST (APPEND examples_PROGRAMS
    example_irreducible_polynomials.cc
    example_sequence_sobol.cc
    example_simple_two_dim.cc
)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

# WithoutExtension
FOREACH (source_file ${examples_PROGRAMS})
    GET_FILENAME_COMPONENT (source_file_we ${source_file} NAME_WE)
    ADD_EXECUTABLE (
        ${source_file_we}
        ${source_file}
    )
    TARGET_LINK_LIBRARIES (${source_file_we}
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
