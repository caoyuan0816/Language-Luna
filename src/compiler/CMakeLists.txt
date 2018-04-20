cmake_minimum_required (VERSION 3.5)

project (LUNAC)

# Include directories
include_directories("generator")

# sub directories
add_subdirectory(generator)
add_subdirectory(parser)
