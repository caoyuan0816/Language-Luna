cmake_minimum_required (VERSION 3.9.1)
project (LUNA)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(main)
add_subdirectory(test)
