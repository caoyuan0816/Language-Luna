cmake_minimum_required (VERSION 3.5)
project (LUNA_LIB)

aux_source_directory(. DIR_SRCS)

add_library(libluna STATIC ${DIR_SRCS})
