/*
=============================================================================
CSR Matrix unit tests
=============================================================================
@File    :   test_SparseMatrix_CSR.cpp
@Date    :   2022/11/04
@Author  :   M.A. Saja Abdul Kaiyoom
@Description :
*/

// =============================================================================
// Standard Library Includes
// =============================================================================

// =============================================================================
// Extension Includes
// =============================================================================
#include "SparseMatrix_CSR.hpp"
#include "unit_test_framework.hpp"

// ==============================================================================
// Compile-time constants
// ==============================================================================
#define N 10

// Tests both double and float implementation
#ifdef TEST_DOUBLE
using fp_type = double;
#endif

#ifdef TEST_FLOAT
using fp_type = float;
#endif

// Use float if neither TEST_DOUBLE or TEST_FLOAT are defined
#ifndef TEST_DOUBLE
#ifndef TEST_FLOAT
using fp_type = float;
#endif
#endif

// Check that the matrix has the correct number of rows, columns and non-zeros
// after setting some entries
TEST(buildingTest) {
  // Create an NxN JDS matrix
  SpMV::SparseMatrix_CSR<fp_type> matrix(N, N);

  // Check that numRows and numCols are N, that numNonZeros = 0, and that the
  // matrix is in the initialized state
  ASSERT_EQUAL(matrix.getNumRows(), N);
  ASSERT_EQUAL(matrix.getNumCols(), N);
  ASSERT_EQUAL(matrix.getNumNonZeros(), 0);
  ASSERT_EQUAL(matrix.getState(), SpMV::initialized);

  // Set the diagonals to 1 (create an identity matrix)
  for (size_t ii = 0; ii < N; ii++) {
    matrix.setCoefficient(ii, ii, 1.0);
  }

  // Check that numNonZeros = N, and that the matrix is in the building state
  ASSERT_EQUAL(matrix.getNumNonZeros(), N);
  ASSERT_EQUAL(matrix.getState(), SpMV::building);

  // Assemble the matrix and check the status
  matrix.assembleStorage();
  ASSERT_EQUAL(matrix.getState(), SpMV::assembled);

  // Check that setting another coefficient returns the matrix to the building
  // state
  matrix.setCoefficient(0, 0, 2.0);
  ASSERT_EQUAL(matrix.getState(), SpMV::building);
}
