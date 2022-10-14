cmake_minimum_required(VERSION 3.10.0)

project(SpMV VERSION 0.1.0)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(examples)