# Declare the minimum version of cmake required
cmake_minimum_required(VERSION 2.8)

# Declare a cmake project
project(HelloSLAM)

# Setting the compilation mode
set(CMAKE_BUILD_TYPE "Debug")

# Add an executable program
# Syntax: add_executable( program name source code file )
add_executable(helloSLAM helloSLAM.cpp)

# Adding the hello library
add_library(hello libHelloSLAM.cpp)
# shared library
add_library(hello_shared SHARED libHelloSLAM.cpp)

# Adding an executable program to call functions in the hello library
add_executable(useHello useHello.cpp)
# Linking library files to an executable program
target_link_libraries(useHello hello_shared)
