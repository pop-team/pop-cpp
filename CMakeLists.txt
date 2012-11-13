cmake_minimum_required(VERSION 2.6)

project(POPCPP)

include(CheckIncludeFile)
include(CheckLibraryExists)

find_package(Threads)

#check_include_file(dlfcn.h HAVE_DLFCN_H)
#check_library_exists(dl dlclose "" HAVE_LIBDL)

set(VERSION 2.6.3)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_subdirectory(parser)
add_subdirectory(lib)
add_subdirectory(interconnector)


