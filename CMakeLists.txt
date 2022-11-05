cmake_minimum_required(VERSION 3.10.0)

project(SpMV VERSION 0.1.0)

include(CTest)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(add_unit_test)

add_subdirectory(src)
# add_subdirectory(examples)
add_subdirectory(tests)

enable_testing()
