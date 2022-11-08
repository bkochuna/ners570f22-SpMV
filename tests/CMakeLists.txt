
# Declare a target library and associated sources
# Add the directory with sources to the header file include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(SpMV
            unit_test_framework.cpp
)

