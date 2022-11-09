/*
=============================================================================
DEN Matrix unit tests
=============================================================================
*/

// =============================================================================
// Standard Library Includes
// =============================================================================

// =============================================================================
// Extension Includes
// =============================================================================
#include "SparseMatrix.hpp"
#include "SparseMatrix_DEN.hpp"
#include "unit_test_framework.hpp"

// ==============================================================================
// Compile-time constants
// ==============================================================================
#define N 4

// Check overloaded constructor
TEST(overloadedConstructorTest) {
  float a[N][N] = {0, 1.1, 5, 0};
  // Create an NxN JDS matrix
  SpMV::SparseMatrix_DEN<fp_type> matrix(N, N, a);

  // Check that numRows and numCols are N, that numNonZeros = 0, and that the
  // matrix is in the initialized state
  ASSERT_EQUAL(matrix.getNumRows(), N);
  ASSERT_EQUAL(matrix.getNumCols(), N);
  ASSERT_EQUAL(matrix.getNumNonZeros(), 2);
  ASSERT_EQUAL(matrix.getState(), SpMV::assembled);
}
