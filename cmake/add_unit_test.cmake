macro(add_unit_test test_name)
  add_executable(${test_name}_double  ${test_name}.cpp)
  add_executable(${test_name}_float ${test_name}.cpp)

  target_compile_options(${test_name}_double PRIVATE -D TEST_DOUBLE)
  target_compile_options(${test_name}_float PRIVATE -D TEST_FLOAT)

  add_test(NAME ${test_name}_double COMMAND ${test_name}_double WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  add_test(NAME ${test_name}_float COMMAND ${test_name}_float WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endmacro(add_unit_test)
