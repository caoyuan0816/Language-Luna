cmake_minimum_required (VERSION 3.5)
project (LUNA_RUNTIME)

#Setting Google Test Framework
#find_package(Threads REQUIRED)
#include(ExternalProject)

#ExternalProject_Add(
#    gtest
#    URL https://github.com/google/googletest/archive/master.zip
#    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
#    INSTALL_COMMAND ""
#)

#ExternalProject_Get_Property(gtest source_dir binary_dir)

#add_library(libgtest IMPORTED STATIC GLOBAL)
#add_dependencies(libgtest gtest)

#set_target_properties(libgtest PROPERTIES
#    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
#    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
#)

#add_library(libgmock IMPORTED STATIC GLOBAL)
#add_dependencies(libgmock gtest)

#set_target_properties(libgmock PROPERTIES
#    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
#    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
#)

# Include directories
#include_directories("${source_dir}/googletest/include"
#                    "${source_dir}/googlemock/include"
#                    "luna")
include_directories("luna")
enable_testing()

#add_test(
#    bin/luna_test bin/luna_test
#)

# sub directories
add_subdirectory(luna)
add_subdirectory(main)
#add_subdirectory(test)
