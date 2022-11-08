# Run add test macro in cmake directory
# Add new test files by writing:
#
# add_unit_test(file-name)
#
# Where file-name does not have .cpp
add_unit_test(example)
add_unit_test(test_SparseMatrix_JDS)

# Declare a target library and associated sources
# Add the directory with sources to the header file include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
