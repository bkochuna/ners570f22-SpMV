/*
=============================================================================
JDS Matrix unit tests
=============================================================================
@File    :   test_SparseMatrix_JDS.cpp
@Date    :   2022/11/04
@Author  :   Alasdair Christison Gray
@Description :
*/

// =============================================================================
// Standard Library Includes
// =============================================================================

// =============================================================================
// Extension Includes
// =============================================================================
#include "../src/SparseMatrix_JDS.hpp"
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

// Check that the matrix has the correct number of rows, columns and non-zeros after setting some entries
TEST(buildingTest) {
  // Create an NxN JDS matrix
  SpMV::SparseMatrix_JDS<fp_type> matrix(N, N);

  // Check that numRows and numCols are N, that numNonZeros = 0, and that the matrix is in the initialized state
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

  // Check that setting another coefficient returns the matrix to the building state
  matrix.setCoefficient(0, 0, 2.0);
  ASSERT_EQUAL(matrix.getState(), SpMV::building);
}

// Check that we get the expected behaviour from y = A*x when A is a diagonal matrix
TEST(IdentityMatVec) {
  // Create an NxN JDS matrix
  SpMV::SparseMatrix_JDS<fp_type> matrix(N, N);

  // Create vectors
  fp_type x[N], y[N], y_expected[N];

  // Set the diagonals to 1 (create an identity matrix)
  for (size_t ii = 0; ii < N; ii++) {
    y_expected[ii] = ((fp_type)rand() / (RAND_MAX));
    matrix.setCoefficient(ii, ii, y_expected[ii]);
  }

  matrix.assembleStorage();

  // Set x to random values
  for (unsigned int ii = 0; ii < N; ii++) {
    x[ii] = ((fp_type)rand() / (RAND_MAX));
    y_expected[ii] *= x[ii];
  }

  // Do the matrix vector multiplication and check that y = x
  matrix.computeMatVecProduct(x, y);
  for (unsigned int ii = 0; ii < N; ii++) {
    ASSERT_EQUAL(y[ii], y_expected[ii]);
  }
}

// Run the tests
TEST_MAIN();
