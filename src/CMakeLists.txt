# Add the directory with sources to the header file include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(SpMV
            SparseMatrix.cpp
            SparseMatrix_JDS.hpp
)

# Set a CMake variable as a list of private headers to include for installation
set(SpMV_PRIVATE_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/SparseMatrix.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/SparseMatrix_DEN.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/SparseMatrix_COO.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/SparseMatrix_JDS.hpp"
)


# Define install target and properties
set_target_properties(SpMV PROPERTIES PUBLIC_HEADER  "${CMAKE_CURRENT_SOURCE_DIR}/SpMV.hpp")
set_target_properties(SpMV PROPERTIES PRIVATE_HEADER "${SpMV_PRIVATE_HEADERS}")
install(TARGETS SpMV)
