cmake_minimum_required(VERSION 3.3)
project(Tasks)

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "C:\\opencv\\mingw-build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(task_cv main.cpp)
add_executable(contours contours.cpp)
add_executable(task2 task2.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs opencv_videoio opencv_photo opencv_features2d)

# linking
target_link_libraries(task_cv ${OpenCV_LIBS})
target_link_libraries(contours ${OpenCV_LIBS})
target_link_libraries(task2 ${OpenCV_LIBS})