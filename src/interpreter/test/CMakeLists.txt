cmake_minimum_required (VERSION 3.5)
project (LUNA_TEST)

add_definitions(-DROOTPATH="${CMAKE_CURRENT_LIST_DIR}")
#message("${CMAKE_CURRENT_LIST_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Setting Luna test
aux_source_directory(. DIR_SRCS)

add_executable(luna_test ${DIR_SRCS} )
target_link_libraries(luna_test
    libluna
    libgtest
    libgmock
)
