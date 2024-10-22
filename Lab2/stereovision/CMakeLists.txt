cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE "Release")
# Add c++ 14 standard support
set(CMAKE_CXX_FLAGS "-std=c++14 -O2")

# Eigen
include_directories("/usr/include/eigen3")

# Finding OpenCV Libraries
find_package(OpenCV REQUIRED)
# Adding Header Files
include_directories(${OpenCV_INCLUDE_DIRS})

# add_subdirectory(imageBasics)
add_subdirectory(stereo)
add_subdirectory(rgbd)
