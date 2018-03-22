cmake_minimum_required(VERSION 3.0)

project(AndroMLProject)

############################################################
# Libraries
############################################################

# OpenCV: computer vision
find_package(OpenCV REQUIRED core imgproc highgui calib3d)
include_directories(${OPENCV_INCLUDE_DIR})

add_subdirectory(andronn)
include_directories(andronn)

add_subdirectory(androprob)
include_directories(androprob)


set(OUTPUT_BINARIES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")


if(MSVC)
    #copy opencv dlls to bin folder
    file(GLOB OPENCV_DLLS "${_OpenCV_LIB_PATH}/*.dll" )
    file(COPY ${OPENCV_DLLS} DESTINATION "${OUTPUT_BINARIES_PATH}/Release")
    file(COPY ${OPENCV_DLLS} DESTINATION "${OUTPUT_BINARIES_PATH}/Debug")
endif(MSVC)



add_subdirectory(samples)


