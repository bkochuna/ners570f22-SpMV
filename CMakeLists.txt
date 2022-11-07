cmake_minimum_required(VERSION 3.10.0)

project(SpMV VERSION 0.1.0)

# Setup language features
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Declare a target library and associated sources
# Add the directory with sources to the header file include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(SpMV
            SparseMatrix.cpp
)
add_executable(example_main
               example_main.cpp)

target_link_libraries(example_main SpMV)