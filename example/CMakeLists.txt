add_executable(testbed2d_example
        main.cpp
        simulation/Sumo.cpp
        simulation/SensorTest.cpp
)
target_link_libraries(testbed2d_example PRIVATE
        testbed2d
)