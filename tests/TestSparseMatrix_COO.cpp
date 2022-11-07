// Testing library required for testing
#include "unit_test_framework.hpp"
#include "SparseMatrix_COO.hpp"

// // Include code needed to test
#include <vector>

#define N 10

// Tests both double and float implementation
 #ifdef TEST_DOUBLE
 using fp_type = double;
 #endif

 #ifdef TEST_FLOAT
 using fp_type = float;
 #endif

 // Check that the matrix has the correct number of rows, columns and non-zeros after setting some entries
  TEST(assemble_Test_COO) {
    // Create an NxN COO matrix
    SpMV::SparseMatrix_COO<fp_type> matrix(N, N);

    // Check that numRows and numCols are N, that numNonZeros = 0, and that the matrix is in the initialized state
    ASSERT_EQUAL(matrix.getNumRows(), N);
    ASSERT_EQUAL(matrix.getNumCols(), N);
    ASSERT_EQUAL(matrix.getNumNonZeros(), 0);
    // Set the diagonals to 1 (create an identity matrix)
    for (size_t ii = 0; ii < N; ii++) {
        matrix.setCoefficient(ii, ii, 1.0);
              }

    // Check that numNonZeros = N, and that the matrix is in the building state
    ASSERT_EQUAL(matrix.getNumNonZeros(), N);

    // Assemble the matrix and check the status
    matrix.assembleStorage();
    ASSERT_EQUAL(matrix.getState(), SpMV::assembled);
    // Check unasemble state
    matrix._unAssemble();
    ASSERT_EQUAL(matrix.getState(), SpMV::unassembled);
    //ASSERT_EQUAL(J, NULL);
                                            }

TEST_MAIN(); 