add_library(utilities
  Utils.hpp
  Utils.cpp
  )
  
  target_link_libraries(utilities
  ${OpenCV_LIBS}
 )
