cmake_minimum_required(VERSION 3.0)

add_executable(test_prob testprob.cpp)
target_link_libraries(test_prob
  ${OpenCV_LIBS}
  androprob
 )

SET(EXECUTABLE_OUTPUT_PATH "${OUTPUT_BINARIES_PATH}")
