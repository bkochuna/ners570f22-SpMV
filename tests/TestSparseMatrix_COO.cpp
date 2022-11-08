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
 ASSERT_EQUAL(matrix.getState(), SpMV::building);
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
 ASSERT_EQUAL(matrix.getState(), SpMV::building);
 
 // Check for not correct result
 ASSERT_NOT_EQUAL(matrix.getState(), SpMV::assembled); 
 
 // check for empty unassemble
 ASSERT_TRUE(J.empty());

  
}

TEST_MAIN(); 
