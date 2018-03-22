cmake_minimum_required(VERSION 3.0)

if (OpenCV_FOUND)
	message(STATUS "OpenCV found - building opencv examples")
	add_subdirectory(testprob)
    add_subdirectory(testem)
else()
	message(STATUS "OpenCV not found - skipping opencv examples")
endif()

add_subdirectory(testnn)