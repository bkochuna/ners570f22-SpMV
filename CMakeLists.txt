cmake_minimum_required(VERSION 3.10.0)

project(SpMV VERSION 0.1.0)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Make add_unit_test visual to the project in more than just the cmake directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(add_unit_test)

# Include the src directory to include in unit tests
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add directories
add_subdirectory(src)
add_subdirectory(examples)

# Allow unit tests and add testing directory
enable_testing()
add_subdirectory(tests)

# install pre-commit via pip for git formatting/linting hooks
# Code adapted from https://www.scivision.dev/cmake-install-python-package/
find_package(Python COMPONENTS Interpreter REQUIRED)

# Do a user install if not using a virtual environment
if(DEFINED ENV{VIRTUAL_ENV} OR DEFINED ENV{CONDA_PREFIX})
  set(_pip_args)
else()
  set(_pip_args "--user")
endif()

execute_process(COMMAND ${Python_EXECUTABLE} -m pip install ${_pip_args} pre-commit)
execute_process(COMMAND pre-commit install)
set_target_properties(SpMV PROPERTIES PUBLIC_HEADER "SparseMatrix.hpp;SparseMatrix_COO.hpp;SparseMatrix_JDS.hpp;SparseMatrix_ELL.hpp;SparseMatrix_CSR.hpp;SparseMatrix_DEN.hpp")

# Install
install(TARGETS SpMV LIBRARY DESTINATION bin)
install(FILES ${PUBLIC_HEADERS} DESTINATION bin/SpMV)