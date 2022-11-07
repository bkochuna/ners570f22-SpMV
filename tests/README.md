# Unit Testing

Here is a guide of how to add unit tests and the structure of the `tests` directory. A detailed example of what a testing file should look like is provided in `tests/example.cpp` and `tests/CMakeLists.cpp`.

## Structure

Each file in `src` should have a corresponding testing file titled `testSourceFilename.cpp` where `SourceFilename.cpp` is the name of the source file.

## Test File Specifics

The unit tests will use the functions and macros defined in the `unit_test_framework.hpp` file. In each testing file this should be included as well as any of the dependencies required such as the corresponding file that is being tested. Both `double` and `float` are tested with the generic type `fp_type`. Anywhere the source code should be tested for double or float implementations, `fp_type` should be passed. Each unit test is defined using the `TEST` macro with the corresponding unit test name. For example:

```cpp
TEST(test_name) {
  // Place test here
}
```
After all the unit tests are defined the file is finished with `TEST_MAIN();`.

This framework provides several assertion functions to use within each unit test:

- `ASSERT_EQUAL(first, second)`: Passes if `first == second`
- `ASSERT_NOT_EQUAL(first, second)`: Passes if `first != second`
- `ASSERT_ALMOST_EQUAL(first, second, precision)`: Passes if `first` is within `precision` of `second`
- `ASSERT_SEQUENCE_EQUAL(first, second)`: Passes if all values in `first` equal those in `second` (they could be arrays or vectors)
- `ASSERT_FALSE(value)`: Passes if `value` is false
- `ASSERT_TRUE(value)`: Passes if `value` is true

## Running with CMake

Prior to compiling add the test file name to the `tests/CMakeLists.txt` file. Do so by adding `add_unit_test(test-file-name)` where `test-file-name` is the name of the testing file without the `.cpp` extension. Then the project can be compiled and the tests can be ran using `make test` or `ctest`.
