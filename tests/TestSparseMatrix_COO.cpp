// Testing library required for testing
#include "unit_test_framework.hpp"
#include "SparseMatrix_COO.hpp"

// // Include code needed to test
#include <vector>

#define N 10
#define M 34
#define RAND_VALUE ((fp_type)rand() / (RAND_MAX))
#define SPARSITY 0.15
#define NUM_MATVEC_TESTS 61

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
TEST(assemble_Test_COO) {
 // Create an NxN COO matrix
 SpMV::SparseMatrix_COO<fp_type> matrix(N, N);
 // Check that numRows and numCols are N, that numNonZeros = 0, and that the matrix is in the initialized state
 ASSERT_EQUAL(matrix.getNumRows(), N);
 ASSERT_EQUAL(matrix.getNumCols(), N);
 ASSERT_EQUAL(matrix.getNumNonZeros(), 0);
 // Set the diagonals to 1 (create an identity matrix)
 for (size_t ii = 0; ii < N; ii++) 
 {
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
 // Check for not correct result
 ASSERT_NOT_EQUAL(matrix.getState(), SpMV::assembled); 
}

TEST(alternateBuildingTest) {
 fp_type val[8]={3,4,7,81,20,-3,-14,6};
 size_t i[8]={1,2,3,5,6,10,11,12};
 size_t j[8]={1,7,7,6,10,13,11,12};
 size_t rows=14;
 size_t cols=14;
 size_t num_non_zero = 8; 
 SpMV::SparseMatrix_COO<fp_type> matrix(rows, cols);
 
 for (size_t ii = 0; ii < num_non_zero; ii++) 
 {
   matrix.setCoefficient(i[ii], j[ii], val[ii]);
 }
  
 // Check that numNonZeros = 8
 ASSERT_EQUAL(matrix.getNumNonZeros(), 8);
 
 // Assemble the matrix and check the status
 matrix.assembleStorage();
 ASSERT_EQUAL(matrix.getState(), SpMV::assembled);
 
 // Check for not correct result
 ASSERT_NOT_EQUAL(matrix.getState(), SpMV::building); 
 
 // Check that numRows and numCols are N, that numNonZeros = 0, and that the matrix is in the initialized state
 ASSERT_EQUAL(matrix.getNumRows(), rows);
 ASSERT_EQUAL(matrix.getNumCols(), cols);
 ASSERT_EQUAL(matrix.getNumNonZeros(), 8);
 ASSERT_TRUE(J[2], j[2]);
 ASSERT_FALSE(J[2], j[0]);
 
 // Check unasemble state
 matrix._unAssemble();
 ASSERT_EQUAL(matrix.getState(), SpMV::unassembled);
 
 // Check for not correct result
 ASSERT_NOT_EQUAL(matrix.getState(), SpMV::assembled); 
 
 // check for empty unassemble
 ASSERT_TRUE(J.empty());

  
}
// Checks the behaviour from y = A*x when A is a diagonal matrix
TEST(DiagonalMatVec) {
  srand(0);
  // Create an NxN COO matrix
  SpMV::SparseMatrix_COO<fp_type> matrix(N, N);
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
  // recompute the matVec and check the result is as expected
  matrix.setCoefficient(0, 0, 1.0);
  matrix.assembleStorage();
  ASSERT_EQUAL(matrix.getState(), SpMV::assembled);
  ASSERT_EQUAL(matrix.getNumNonZeros(), N);
  matrix.computeMatVecProduct(x, y);
  ASSERT_EQUAL(y[0], x[0]);
}
// Tests a series of random matrix-vector products on MxN sparse matrix
TEST(RandomMatVec) {
  srand(0);
  for (int n = 0; n < NUM_MATVEC_TESTS; n++) {
    // Create an MxN COO matrix
    SpMV::SparseMatrix_COO<fp_type> matrix(M, N);
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
TEST_MAIN(); 
