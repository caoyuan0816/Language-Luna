cmake_minimum_required (VERSION 3.5)
project (LUNA_COMPILER_GENERATOR)

aux_source_directory(. DIR_SRCS)

add_library(liblunac STATIC ${DIR_SRCS})
