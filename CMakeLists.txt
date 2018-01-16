cmake_minimum_required(VERSION 3.0)

add_subdirectory(andronn)
include_directories(andronn)

add_executable(test_example test.cpp)
target_link_libraries(test_example andronn)

