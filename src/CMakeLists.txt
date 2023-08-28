add_library(testbed2d STATIC
        draw.cpp
        test.cpp
        testbed2d.cpp
        ../example/main.cpp
)
target_include_directories(testbed2d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

find_package(box2d CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(testbed2d PUBLIC
        box2d::box2d
        glad::glad
        imgui::imgui
        glfw
)