cmake_minimum_required (VERSION 3.5)
project (LUNA_Interpreter)

#find_library(LUNA_LIB libluna)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

aux_source_directory(. DIR_SRCS)

add_executable(luna ${DIR_SRCS})

target_link_libraries(luna
    libluna
)

install(TARGETS luna DESTINATION bin)

