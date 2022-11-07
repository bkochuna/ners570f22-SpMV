cmake_minimum_required(VERSION 3.10.0)

project(SpMV VERSION 0.1.0)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(examples)

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
