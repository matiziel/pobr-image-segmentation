cmake_minimum_required(VERSION 3.24)
project(pobr_image_segmentation)


set(CMAKE_CXX_STANDARD 17)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(pobr_image_segmentation main.cpp ColourHLS.h BoundingBox.h ImageProcessor.cpp ImageProcessor.h Histogram.cpp Histogram.h Utils.h Converter.h Segment.cpp Segment.h Segmentation.cpp Segmentation.h ColourProvider.h Config.h Recognition.cpp Recognition.h Segment.cpp)
target_link_libraries( pobr_image_segmentation ${OpenCV_LIBS} )
