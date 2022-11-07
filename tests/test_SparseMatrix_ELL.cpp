/*
=============================================================================
COO Matrix unit tests
=============================================================================
@File    :   test_SparseMatrix_ELL.cpp
@Date    :   2022/11/07
@Author  :   Doruk Aksoy (Replicating the work of Alasdair Christison Gray for JDS)
@Description :
*/

// =============================================================================
// Standard Library Includes
// =============================================================================

// =============================================================================
// Extension Includes
// =============================================================================
#include "SparseMatrix_ELL.hpp"
#include "unit_test_framework.hpp"

// ==============================================================================
// Compile-time constants
// ==============================================================================
#define M 123
#define N 456
#define RAND_VALUE ((fp_type)rand() / (RAND_MAX))
#define SPARSITY 0.15
#define NUM_MATVEC_TESTS 100

// Check that the matrix has the correct number of rows, columns and non-zeros
// after setting some entries
TEST(buildingTest) {
  // Create an NxN ELL matrix
  SpMV::SparseMatrix_ELL<fp_type> matrix(N, N);

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

  // Check that changing an existing value returns the matrix to a building state and doesn't change the number of
  // non-zeros
  matrix.setCoefficient(0, 0, 2.0);
  ASSERT_EQUAL(matrix.getNumNonZeros(), N);
  ASSERT_EQUAL(matrix.getState(), SpMV::building);
}

// Check that we get the expected behaviour from y = A*x when A is a diagonal
// matrix
TEST(DiagonalMatVec) {
  srand(0);
  // Create an NxN ELL matrix
  SpMV::SparseMatrix_ELL<fp_type> matrix(N, N);

  // Create vectors
  fp_type x[N], y[N], y_expected[N];

  // Set the diagonals to random values
  for (size_t ii = 0; ii < N; ii++) {
    y_expected[ii] = RAND_VALUE;
    matrix.setCoefficient(ii, ii, y_expected[ii]);
  }

  matrix.assembleStorage();

  // Set x to random values
  for (unsigned int ii = 0; ii < N; ii++) {
    x[ii] = RAND_VALUE;
    y_expected[ii] *= x[ii];
  }

  // Do the matrix vector multiplication and check that y = x
  matrix.computeMatVecProduct(x, y);
  for (unsigned int ii = 0; ii < N; ii++) {
    ASSERT_EQUAL(y[ii], y_expected[ii]);
  }

  // To test that the _unassemble/assemble process works correctly, update the values of one of the diagonal entries,
  // recompute the matvec and check the result is as expected
  matrix.setCoefficient(0, 0, 1.0);
  matrix.assembleStorage();
  ASSERT_EQUAL(matrix.getState(), SpMV::assembled);
  ASSERT_EQUAL(matrix.getNumNonZeros(), N);
  matrix.computeMatVecProduct(x, y);
  ASSERT_EQUAL(y[0], x[0]);
}

// Test a series of random matrix-vector products
TEST(RandomMatVec) {
  srand(0);

  for (int n = 0; n < NUM_MATVEC_TESTS; n++) {

    // Create an MxN ELL matrix
    SpMV::SparseMatrix_ELL<fp_type> matrix(M, N);

    // Create the vector to be multiplied, the vector to store the MatVec result in, and the vector to store the
    // expected result in
    fp_type x[N], y[N], y_expected[N];

    // Set x to random values, expected y to 0
    for (unsigned int ii = 0; ii < N; ii++) {
      x[ii] = RAND_VALUE;
      y_expected[ii] = 0.0;
    }

    // Go through each entry of the matrix and randomly assign random values
    for (unsigned int rowInd = 0; rowInd < M; rowInd++) {
      for (unsigned int colInd = 0; colInd < N; colInd++) {
        if (RAND_VALUE < SPARSITY) {
          // Set the coefficient to a random value
          fp_type value = RAND_VALUE;
          matrix.setCoefficient(rowInd, colInd, value);

          // Add the value to the expected result
          y_expected[rowInd] += value * x[colInd];
        }
      }
    }

    // Assemble the matrix
    matrix.assembleStorage();

    // Do the matrix vector multiplication and check that y contains the row sums of the matrix
    matrix.computeMatVecProduct(x, y);
    for (unsigned int ii = 0; ii < N; ii++) {
      ASSERT_ALMOST_EQUAL(y[ii], y_expected[ii], 1e-10);
    }
  }
}

// Run the tests
TEST_MAIN();
