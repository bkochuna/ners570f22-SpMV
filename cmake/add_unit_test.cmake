# Macro to add unit tests easily
macro(add_unit_test test_name)
  # Add executable for both float and double to the project
  add_executable(${test_name}_double  ${test_name}.cpp)
  add_executable(${test_name}_float ${test_name}.cpp)

  # Compile with -D for what type fp_type is
  target_compile_options(${test_name}_double PRIVATE -D __SPMV_FPTYPE__=double)
  target_compile_options(${test_name}_float PRIVATE -D __SPMV_FPTYPE__=float)

  # Add test
  add_test(NAME ${test_name}_double COMMAND ${test_name}_double WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  add_test(NAME ${test_name}_float COMMAND ${test_name}_float WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endmacro(add_unit_test)
