// Testing library required for testing
#include "unit_test_framework.hpp"

// Include code needed to test
#include "../src/SpMVFactory.hpp"
#include <typeinfo>

/* Here are some examples of unit tests for std::vector, the code being tested
 * is included as well as the unit testing framework file. The unit testing
 * framework defines all the macros and functions you'll need. Define a unit
 * test as TEST(name) where 'name' is the name of the test you'll give it (no
 * spaces). Then initialize whatever class of data you need to test, implement
 * your test and use the following assertion macros:
 *
 * ASSERT_EQUAL(first, second);
 * ASSERT_NOT_EQUAL(first, second);
 * ASSERT_ALMOST_EQUAL(first, second, precision);
 * ASSERT_SEQUENCE_EQUAL(first, second);
 * ASSERT_FALSE(value);
 * ASSERT_TRUE(value);
 *
 * Finally run all tests in the file using TEST_MAIN();
 * Some examples are provided below
 */

// Create a unit test
TEST(COOFactory) {
  // Initialize Factories
  SpMV::SpMVFactory<double> *spmvfDouble = new SpMV::SparseMatrixFactory_COO<double>();
  SpMV::SpMVFactory<float> *spmvfFloat = new SpMV::SparseMatrixFactory_COO<float>();
  // Fake row and column counts
  size_t nRow=10, nCol = 11;
  // Initialize Matrices
  SpMV::SparseMatrix<double> *spmvDouble = spmvfDouble->createSparseMatrix(nRow,nCol);
  SpMV::SparseMatrix<float> *spmvFloat = spmvfFloat->createSparseMatrix(nRow,nCol);

  // Assertions for unit testing factory
  ASSERT_TRUE(typeid(spmvfDouble)==typeid(SpMV::SpMVFactory<double> *));
  ASSERT_TRUE(typeid(spmvfFloat)==typeid(SpMV::SpMVFactory<float> *));
  ASSERT_TRUE(typeid(*spmvfDouble)==typeid(SpMV::SparseMatrixFactory_COO<double>));
  ASSERT_TRUE(typeid(*spmvfFloat)==typeid(SpMV::SparseMatrixFactory_COO<float>));

  // Assertions for unit testing matrix
  ASSERT_TRUE(typeid(spmvDouble)==typeid(SpMV::SparseMatrix_COO<double> *));
  ASSERT_TRUE(typeid(spmvFloat)==typeid(SpMV::SparseMatrix_COO<float> *));
  ASSERT_TRUE(typeid(*spmvDouble)==typeid(SpMV::SparseMatrix_COO<double>));
  ASSERT_TRUE(typeid(*spmvFloat)==typeid(SpMV::SparseMatrix_COO<float>));
}
// Create a unit test
TEST(ELLFactory) {
  // Initialize Factories
  SpMV::SpMVFactory<double> *spmvfDouble = new SpMV::SparseMatrixFactory_ELL<double>();
  SpMV::SpMVFactory<float> *spmvfFloat = new SpMV::SparseMatrixFactory_ELL<float>();
  // Fake row and column counts
  size_t nRow=10, nCol = 11;
  // Initialize Matrices
  SpMV::SparseMatrix<double> *spmvDouble = spmvfDouble->createSparseMatrix(nRow,nCol);
  SpMV::SparseMatrix<float> *spmvFloat = spmvfFloat->createSparseMatrix(nRow,nCol);

  // Assertions for unit testing factory
  ASSERT_TRUE(typeid(spmvfDouble)==typeid(SpMV::SpMVFactory<double> *));
  ASSERT_TRUE(typeid(spmvfFloat)==typeid(SpMV::SpMVFactory<float> *));
  ASSERT_TRUE(typeid(*spmvfDouble)==typeid(SpMV::SparseMatrixFactory_ELL<double>));
  ASSERT_TRUE(typeid(*spmvfFloat)==typeid(SpMV::SparseMatrixFactory_ELL<float>));

  // Assertions for unit testing matrix
  ASSERT_TRUE(typeid(spmvDouble)==typeid(SpMV::SparseMatrix_ELL<double> *));
  ASSERT_TRUE(typeid(spmvFloat)==typeid(SpMV::SparseMatrix_ELL<float> *));
  ASSERT_TRUE(typeid(*spmvDouble)==typeid(SpMV::SparseMatrix_ELL<double>));
  ASSERT_TRUE(typeid(*spmvFloat)==typeid(SpMV::SparseMatrix_ELL<float>));
}
// Create a unit test
TEST(CSRFactory) {
  // Initialize Factories
  SpMV::SpMVFactory<double> *spmvfDouble = new SpMV::SparseMatrixFactory_CSR<double>();
  SpMV::SpMVFactory<float> *spmvfFloat = new SpMV::SparseMatrixFactory_CSR<float>();
  // Fake row and column counts
  size_t nRow=10, nCol = 11;
  // Initialize Matrices
  SpMV::SparseMatrix<double> *spmvDouble = spmvfDouble->createSparseMatrix(nRow,nCol);
  SpMV::SparseMatrix<float> *spmvFloat = spmvfFloat->createSparseMatrix(nRow,nCol);

  // Assertions for unit testing factory
  ASSERT_TRUE(typeid(spmvfDouble)==typeid(SpMV::SpMVFactory<double> *));
  ASSERT_TRUE(typeid(spmvfFloat)==typeid(SpMV::SpMVFactory<float> *));
  ASSERT_TRUE(typeid(*spmvfDouble)==typeid(SpMV::SparseMatrixFactory_CSR<double>));
  ASSERT_TRUE(typeid(*spmvfFloat)==typeid(SpMV::SparseMatrixFactory_CSR<float>));

  // Assertions for unit testing matrix
  ASSERT_TRUE(typeid(spmvDouble)==typeid(SpMV::SparseMatrix_CSR<double> *));
  ASSERT_TRUE(typeid(spmvFloat)==typeid(SpMV::SparseMatrix_CSR<float> *));
  ASSERT_TRUE(typeid(*spmvDouble)==typeid(SpMV::SparseMatrix_CSR<double>));
  ASSERT_TRUE(typeid(*spmvFloat)==typeid(SpMV::SparseMatrix_CSR<float>));
}
// Create a unit test
TEST(JDSFactory) {
  // Initialize Factories
  SpMV::SpMVFactory<double> *spmvfDouble = new SpMV::SparseMatrixFactory_JDS<double>();
  SpMV::SpMVFactory<float> *spmvfFloat = new SpMV::SparseMatrixFactory_JDS<float>();
  // Fake row and column counts
  size_t nRow=10, nCol = 11;
  // Initialize Matrices
  SpMV::SparseMatrix<double> *spmvDouble = spmvfDouble->createSparseMatrix(nRow,nCol);
  SpMV::SparseMatrix<float> *spmvFloat = spmvfFloat->createSparseMatrix(nRow,nCol);

  // Assertions for unit testing factory
  ASSERT_TRUE(typeid(spmvfDouble)==typeid(SpMV::SpMVFactory<double> *));
  ASSERT_TRUE(typeid(spmvfFloat)==typeid(SpMV::SpMVFactory<float> *));
  ASSERT_TRUE(typeid(*spmvfDouble)==typeid(SpMV::SparseMatrixFactory_JDS<double>));
  ASSERT_TRUE(typeid(*spmvfFloat)==typeid(SpMV::SparseMatrixFactory_JDS<float>));

  // Assertions for unit testing matrix
  ASSERT_TRUE(typeid(spmvDouble)==typeid(SpMV::SparseMatrix_JDS<double> *));
  ASSERT_TRUE(typeid(spmvFloat)==typeid(SpMV::SparseMatrix_JDS<float> *));
  ASSERT_TRUE(typeid(*spmvDouble)==typeid(SpMV::SparseMatrix_JDS<double>));
  ASSERT_TRUE(typeid(*spmvFloat)==typeid(SpMV::SparseMatrix_JDS<float>));
}
// Create a unit test
TEST(DENFactory) {
  // Initialize Factories
  SpMV::SpMVFactory<double> *spmvfDouble = new SpMV::SparseMatrixFactory_DEN<double>();
  SpMV::SpMVFactory<float> *spmvfFloat = new SpMV::SparseMatrixFactory_DEN<float>();
  // Fake row and column counts
  size_t nRow=10, nCol = 11;
  // Initialize Matrices
  SpMV::SparseMatrix<double> *spmvDouble = spmvfDouble->createSparseMatrix(nRow,nCol);
  SpMV::SparseMatrix<float> *spmvFloat = spmvfFloat->createSparseMatrix(nRow,nCol);

  // Assertions for unit testing factory
  ASSERT_TRUE(typeid(spmvfDouble)==typeid(SpMV::SpMVFactory<double> *));
  ASSERT_TRUE(typeid(spmvfFloat)==typeid(SpMV::SpMVFactory<float> *));
  ASSERT_TRUE(typeid(*spmvfDouble)==typeid(SpMV::SparseMatrixFactory_DEN<double>));
  ASSERT_TRUE(typeid(*spmvfFloat)==typeid(SpMV::SparseMatrixFactory_DEN<float>));

  // Assertions for unit testing matrix
  ASSERT_TRUE(typeid(spmvDouble)==typeid(SpMV::SparseMatrix_DEN<double> *));
  ASSERT_TRUE(typeid(spmvFloat)==typeid(SpMV::SparseMatrix_DEN<float> *));
  ASSERT_TRUE(typeid(*spmvDouble)==typeid(SpMV::SparseMatrix_DEN<double>));
  ASSERT_TRUE(typeid(*spmvFloat)==typeid(SpMV::SparseMatrix_DEN<float>));
}


// Run the unit tests
TEST_MAIN();