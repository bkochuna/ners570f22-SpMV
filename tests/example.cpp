// Testing library required for testing

#include "unit_test_framework.hpp"

// Include code needed to test
#include <vector>

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
TEST(vectorTest) {
  // Initialize variables for testing
  std::vector<fp_type> a = {1, 2, 3};
  std::vector<fp_type> b = {3, 2, 3.00001};

  // Assertions for unit testing
  ASSERT_NOT_EQUAL(a[0], b[0]);            // 1 != 3
  ASSERT_EQUAL(a[1], b[1]);                // 2 == 2
  ASSERT_ALMOST_EQUAL(a[2], b[2], 0.0001); // 3 ~= 3.00001
}

// Create a unit test
TEST(vectorSquence) {
  // Initialize variables for testing
  std::vector<fp_type> a = {1, 2, 3};
  std::vector<fp_type> b = {1, 2, 3};

  // Assertions
  ASSERT_SEQUENCE_EQUAL(a, b);
}

// Create a unit test
TEST(vectorEmpty) {
  // Initialize testing data
  std::vector<fp_type> a;

  // Assert vector is empty
  ASSERT_TRUE(a.empty());

  // Make vector not empty
  a.push_back(5);

  // Assert vector is not empty and at position 0 is 5
  ASSERT_FALSE(a.empty());
  ASSERT_EQUAL(a[0], 5);
}

// Run the 3 unit tests
TEST_MAIN();
