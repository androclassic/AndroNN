cmake_minimum_required(VERSION 3.0)

add_executable(test_nn test.cpp)
target_link_libraries(test_nn andronn)
SET(EXECUTABLE_OUTPUT_PATH "${OUTPUT_BINARIES_PATH}")
