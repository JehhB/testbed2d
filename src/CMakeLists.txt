add_library(testbed2d STATIC
        draw.cpp
        test.cpp
        testbed2d.cpp

        util/Mesh.cpp

        entity/SumoRing.cpp
        entity/Wheel.cpp
		entity/DifferentialDriveCar.cpp
)
target_include_directories(testbed2d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(testbed2d PUBLIC
        glad
        box2d::box2d
        imgui::imgui
        glfw
)