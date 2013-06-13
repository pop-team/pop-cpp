#
# POP-C++ 
# Cross-compilation file for the K Computer
# Must be used with the CMake option -DCMAKE_TOOLCHAIN_FILE=<path_of_this_file>
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

include(CMakeForceCompiler)
set(CMAKE_SYSTEM_NAME KComputer)

# Disable the compilation of the POP-C++ compiler. The POP-C++ compiler should be compiled normally on the front-end. 
set(POPCPP_COMPILER OFF)

# Set the compiler for the K Computer
cmake_force_c_compiler(fccpx GNU)
cmake_force_cxx_compiler(FCCpx GNU)
set(CMAKE_FIND_ROOT_PATH /opt/FJSVtclang/GM-1.2.0-09)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_CXX_OUTPUT_EXTENSION ".o")
set(CMAKE_C_OUTPUT_EXTENSION ".o")
set(CMAKE_CXX_FLAGS "-Xg -pthread")
message(STATUS "COMPILER COMMAND - ${CMAKE_CXX_COMPILE_OBJECT}")
set(CMAKE_CXX_COMPILE_OBJECT "<CMAKE_CXX_COMPILER> <FLAGS> -o <OBJECT>  -c  <SOURCE>")

# Set compiler to compile MPI components
set(MPI_CXX_COMPILER mpiFCCpx)
set(POPCPP_MPI_COMPILER_FLAGS -Xg -pthread -o)
set(POPC_MAIN_FLAGS -Xg -pthread -c)
