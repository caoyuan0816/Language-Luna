cmake_minimum_required (VERSION 3.5)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

SET(CMAKE_CXX_FLAGS "-std=c++0x")

set (CMAKE_CXX_STANDARD 11)

project (LUNA)

# Include directories
include_directories("generator")

# sub directories
add_subdirectory(src)
