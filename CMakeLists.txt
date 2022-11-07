cmake_minimum_required(VERSION 3.10.0)

project(SpMV VERSION 0.1.0)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Make add_unit_test visual to the project in more than just the cmake directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(add_unit_test)

# Include the src directory to include in unit tests
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add directories
add_subdirectory(src)
add_subdirectory(examples)

# Allow unit tests and add testing directory
enable_testing()
add_subdirectory(tests)

# Install
install(TARGETS SpMV DESTINATION bin)