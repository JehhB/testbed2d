cmake_minimum_required(VERSION 3.5)
project(testbed2d VERSION 1.0.0)

option(TESTBED2D_BUILD_EXAMPLES "Build testbed2d examples" ON)

add_subdirectory(src)

if (TESTBED2D_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()