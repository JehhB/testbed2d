cmake_minimum_required(VERSION 3.5)
project(testbed2d VERSION 1.0.0)

option(TESTBED2D_BUILD_EXAMPLES "Build testbed2d examples" ON)

find_package(box2d REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

add_subdirectory(src)

if (TESTBED2D_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()