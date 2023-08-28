add_executable(testbed2d_example
        main.cpp
        add_pair.cpp
)
target_link_libraries(testbed2d_example PRIVATE
        testbed2d
)