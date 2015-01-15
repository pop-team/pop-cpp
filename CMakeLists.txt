cmake_minimum_required(VERSION 2.6)

#
# POP-C++
# Entry point of the build process of POP-C++.
#
# Options:
#  - use -DCMAKE_INSTALL_PREFIX=<install-path> to specify the installation prefix
#  - use -DPOPCPP_COMPILER=OFF to disable the POP-C++ compiler build
#  - use -DMPI_SUPPORT=ON to enable MPI support in POP-C++
#  - use -DXMP_SUPPORT=ON to enable XMP support in POP-C++
#
#
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

project(POPCPP)

# Define version of POP-C++ - It will be shown on the compiler usage message and with -version option
if(WIN32)
  set(VERSION "3.0 - Windows")
elseif(UNIX)
  set(VERSION "3.0 - Linux")
endif(WIN32)

execute_process(COMMAND uname -m OUTPUT_VARIABLE HOST_CPU_RAW)
string(REGEX REPLACE "\n" "" HOST_CPU "${HOST_CPU_RAW}")
execute_process(COMMAND uname -s OUTPUT_VARIABLE HOST_KERNEL_RAW)
string(REGEX REPLACE "\n" "" HOST_KERNEL "${HOST_KERNEL_RAW}")

include(CheckIncludeFile)
include(CheckLibraryExists)

# Check availability of pthread
check_include_file(pthread.h HAVE_PTHREAD_H)
check_library_exists(pthread pthread_create "" HAVE_LIBPTHREAD)
# Check existence of header files and library
#check_include_file(dlfcn.h HAVE_DLFCN_H)
#check_library_exists(dl dlclose "" HAVE_LIBDL)

# Define user specific option. Disable by default.
option(MPI_SUPPORT "MPI Support" OFF)
option(XMP_SUPPORT "XMP Support" OFF)
set(POPCPP_EXTRA_FLAGS "" CACHE STRING "Flags to add to the POP-C++ compiler")

# Set MPI support implicitly if XMP support is required
if(XMP_SUPPORT)
  set(MPI_SUPPORT ON)
endif(XMP_SUPPORT)

# Find MPI installation
if(MPI_SUPPORT)
  if(NOT DEFINED MPI_CXX_COMPILER)
    find_package(MPI REQUIRED)
    message(STATUS "COMPILER FLAGS FOR MPI")
    set(POPCPP_MPI_COMPILER_FLAGS -o)
  endif(NOT DEFINED MPI_CXX_COMPILER)
endif(MPI_SUPPORT)

# Add for linking <winsock2.h>
if(WIN32)
    SET(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lws2_32")
endif(WIN32)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:\\popc")
  elseif(UNIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local/popc")
  endif(WIN32)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


# Set to OFF to configure and compile the POP-C++ compiler/parser separately
option(POPCPP_COMPILER "POP-C++ Compiler compilation" ON)

# Define variable for MPI compilation
#if(NOT DEFINED MPI_COMPILER)
#  set(MPI_COMPILER mpic++)
#endif(NOT DEFINED MPI_COMPILER)

#if(NOT DEFINED MPI_COMPILER_FLAGS)
#  set(MPI_COMPILER_FLAGS -o)
#endif(NOT DEFINED MPI_COMPILER_FLAGS)

if(NOT DEFINED POPC_MAIN_FLAGS)
 set(POPC_MAIN_FLAGS -c)
endif(NOT DEFINED POPC_MAIN_FLAGS)


# Generate the config.h file during the configuration of the project
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

# If the POP-C++ Compilation option is on, add the parser directory as a sub folder
if(POPCPP_COMPILER)
  message(STATUS "POP-C++ Compiler will be build with the same configuration as the library")
  add_subdirectory(parser)
endif(POPCPP_COMPILER)

# Add subdirectory which inlude a CMakeLists.text file
add_subdirectory(lib)
add_subdirectory(include)

# Instruction to enable the MPI support for POP-C++
if(MPI_SUPPORT)
  message(STATUS "MPI Support for POP-C++ is enable")
  add_subdirectory(mpi)
  add_subdirectory(interconnector)
endif(MPI_SUPPORT)

# Instruction to enable the XMP support for POP-C++
if(XMP_SUPPORT)
  message(STATUS "XMP Support for POP-C++ is enable")
  add_subdirectory(xmp)
endif(XMP_SUPPORT)

add_subdirectory(scripts)
add_subdirectory(services)

# Add target to clean the distribution of all CMake generated files
  set(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   CMakeFiles
   cmake.check_cache
   *.cmake
   interconnector/Makefile
   interconnector/*.cmake
   interconnector/CMakeFiles
   mpi/Makefile
   mpi/*.cmake
   mpi/CMakeFiles
   xmp/Makefile
   xmp/*.cmake
   xmp/CMakeFiles
   xmp/src/CMakeFiles
   xmp/src/*.cmake
   xmp/src/Makefile
   lib/Makefile
   lib/*.cmake
   lib/CMakeFiles
   lib/dynamic/Makefile
   lib/dynamic/*.cmake
   lib/dynamic/CMakeFiles
   lib/pseudodynamic/Makefile
   lib/pseudodynamic/*.cmake
   lib/pseudodynamic/CMakeFiles
   include/Makefile
   include/*.cmake
   include/CMakeFiles
   include/dynamic/Makefile
   include/dynamic/*.cmake
   include/dynamic/CMakeFiles
   include/pseudodynamic/Makefile
   include/pseudodynamic/*.cmake
   include/pseudodynamic/CMakeFiles
   scripts/Makefile
   scripts/*.cmake
   scripts/CMakeFiles
   scripts/popcrun
   scripts/popc-runtime-env.in
   scripts/popc-runtime-env.sh
   scripts/popc_script_setup
   scripts/popc_setup
   scripts/SXXpopc
   scripts/popc-user-env.csh
   scripts/popc-user-env.sh
   services/Makefile
   services/*.cmake
   services/CMakeFiles
   services/popcobjrun
   services/lib/Makefile
   services/lib/*.cmake
   services/lib/CMakeFiles
   config.h
   Makefile
   *~
  )

  if(POPCPP_COMPILER)
    set(EXTRACLEANED
      parser/*.cmake
      parser/CMakeFiles
      parser/Makefile
      parser/popcc.cc
    )
  else(POPCPP_COMPILER)
    set(EXTRACLEANED "")
  endif(POPCPP_COMPILER)

  add_custom_target(distclean
      COMMAND ${CMAKE_BUILD_TOOL} clean
      COMMAND rm -Rf CMakeTmp ${DISTCLEANED} ${EXTRACLEANED}
      COMMENT "distribution clean"
      )

  # Custom target to run the tests
  add_custom_target(tests
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/runtests -all
      COMMENT "run all tests"
      )

  # These 3 custom targets (lint, check and indent) can be used to facilitate the code maintenance
  add_custom_target(lint
    COMMENT "Check C++ lint rules with the lint tool provided by Google"
    COMMAND find . -name \"*.h\" -o -name \"*.cpp\" -o -name \"*.cc\" | xargs scripts/cpplint.py --filter=-whitespace,-legal,-build,-runtime/references,-runtime/explicit,-readability/todo,-readability/streams,-readability/function,-runtime/int
  )

  # If you use vim use: setlocal errorformat=[%f:%l]\ ->\ %m,[%f:%l]:%m
  # to jump automatically between errors
  add_custom_target(check
    COMMENT "Check C++ code statically with cppcheck"
    COMMAND cppcheck . --force --enable=all -q
  )

  add_custom_target(indent
    COMMENT "Indent the code automatically with astyle"
    COMMAND find . -name \"*.h\" -o -name \"*.cpp\" -o -name \"*.cc\" -o -name \"*.cc.in\" -o -name \"*.ph\" | xargs astyle -jnUc -A2
  )
