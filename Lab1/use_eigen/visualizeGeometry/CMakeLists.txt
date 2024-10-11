cmake_minimum_required( VERSION 2.8 )
project( visualizeGeometry )

set(CMAKE_CXX_FLAGS "-std=c++14")

# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )

# 添加Pangolin依赖
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_executable( visualizeGeometry visualizeGeometry.cpp )
target_link_libraries( visualizeGeometry ${Pangolin_LIBRARIES} )


# cmake_minimum_required( VERSION 2.8 )
# project( visualizeGeometry )

# set(CMAKE_CXX_FLAGS "-std=c++14")

# # 添加Eigen头文件
# include_directories( "/usr/include/eigen3" )

# # 添加Pangolin依赖
# find_package(Pangolin REQUIRED)
# set(CMAKE_MODULE_PATH "/home/zezhousun/Documents/slambook2/ch3/visualizeGeometry/")
# find_package(epoxy REQUIRED)
# find_package(OpenGL REQUIRED)

# include_directories(${Pangolin_INCLUDE_DIRS} ${epoxy_INCLUDE_DIRS})

# add_executable(visualizeGeometry visualizeGeometry.cpp)
# target_link_libraries(visualizeGeometry ${Pangolin_LIBRARIES})