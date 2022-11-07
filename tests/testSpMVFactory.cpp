// Testing library required for testing
#include "unit_test_framework.hpp"

// Include code needed to test
#include "SpMVFactory.hpp"

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
  // Initialize variables for testing
  SpMV::SpMVFactory<double> *spmvfDouble = SpMV::SparseMatrixFactory_COO<double>().createSparseMatrix();
  SpMV::SpMVFactory<float> *spmvfFloat = SpMV::SparseMatrixFactory_COO<float>().createSparseMatrix();

  // Assertions for unit testing
  ASSERT_TRUE(is_pointer(spmvfDouble));
  ASSERT_TRUE(is_pointer(spmvfFloat));
  ASSERT_TRUE(typeid(*spmvfDouble)==SpMV::SparseMatrixFactory_COO<double>);
  ASSERT_TRUE(typeid(*spmvfFloat)==SpMV::SparseMatrixFactory_COO<float>);
}

// Run the unit tests
TEST_MAIN();