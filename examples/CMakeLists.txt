add_executable(example_main
            example_main.cpp
)
target_include_directories(example_main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)
