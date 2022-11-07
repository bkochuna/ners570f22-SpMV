# Declare a target library and associated sources
# Add the directory with sources to the header file include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(SpMV
            SparseMatrix.cpp
            SparseMatrix_COO.cpp
            SparseMatrix_JDS.cpp
            SparseMatrix_ELL.cpp
            SparseMatrix_CSR.cpp
            SparseMatrix_DEN.cpp
            SparseMatrix.hpp
            SparseMatrix_COO.hpp
            SparseMatrix_JDS.hpp
            SparseMatrix_ELL.hpp
            SparseMatrix_CSR.hpp
            SparseMatrix_DEN.hpp
)