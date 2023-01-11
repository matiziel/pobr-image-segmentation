cmake_minimum_required(VERSION 3.24)
project(pobr_image_segmentation)


set(CMAKE_CXX_STANDARD 17)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(pobr_image_segmentation main.cpp MomentumComputing.cpp MomentumComputing.h ColourHLS.h BoundingBox.h ImageProcessor.cpp ImageProcessor.h)
target_link_libraries( pobr_image_segmentation ${OpenCV_LIBS} )
