# Add the directory with sources to the header file include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_library(SpMV
            SparseMatrix.hpp
            SparseMatrix_JDS.hpp
)
