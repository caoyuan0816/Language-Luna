cmake_minimum_required (VERSION 3.9.1)
project (LUNAC)

# Include directories
include_directories("generator")

# sub directories
add_subdirectory(generator)
add_subdirectory(parser)
