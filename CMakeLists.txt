cmake_minimum_required(VERSION 2.6)

#
# POP-C++ project. This CMakeLists.txt file is the entry point for the compilation of the POP-C++ library and services. 
#

project(POPCPP)

# Define version of POP-C++ - It will be shown on the compiler usage message and with -version option
set(VERSION "2.6.4 - K Computer")
execute_process(COMMAND uname -m OUTPUT_VARIABLE HOST_CPU_RAW)
string(REGEX REPLACE "\n" "" HOST_CPU ${HOST_CPU_RAW})
execute_process(COMMAND uname -s OUTPUT_VARIABLE HOST_KERNEL_RAW)
string(REGEX REPLACE "\n" "" HOST_KERNEL ${HOST_KERNEL_RAW})



include(CheckIncludeFile)
include(CheckLibraryExists)
#find_package(Threads)


check_include_file(pthread.h HAVE_PTHREAD_H)
check_library_exists(pthread pthread_create "" HAVE_LIBPTHREAD)

if(DEFINED CMAKE_THREAD_LIBS_INIT)
  set(HAVE_LIBPTHREAD)
endif(DEFINED CMAKE_THREAD_LIBS_INIT)


# Check existence of header files and library 
#check_include_file(dlfcn.h HAVE_DLFCN_H)
#check_library_exists(dl dlclose "" HAVE_LIBDL)

# Define user specific option. Disable by default.
OPTION(MPI_SUPPORT "MPI Support" OFF)
OPTION(XMP_SUPPORT "XMP Support" OFF)



# Define variable for MPI compilation
if(NOT DEFINED MPI_COMPILER)
  set(MPI_COMPILER mpic++)
endif(NOT DEFINED MPI_COMPILER)

if(NOT DEFINED MPI_COMPILER_FLAGS)
  set(MPI_COMPILER_FLAGS -o)
endif(NOT DEFINED MPI_COMPILER_FLAGS)


if(NOT DEFINED POPC_MAIN_FLAGS)
 set(POPC_MAIN_FLAGS -c)
endif(NOT DEFINED POPC_MAIN_FLAGS)


# Generate the config.h file during the configuration of the project 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

# Add subdirectory which inlude a CMakeLists.text file
add_subdirectory(lib)
add_subdirectory(interconnector)
add_subdirectory(include)

# Install headers files, programs, library and object files



install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/parser/popcc DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/parser/popcpp DESTINATION bin)



# Instruction to enable the MPI support for POP-C++
if(MPI_SUPPORT)
  message(STATUS "MPI Support for POP-C++ is enable")
  add_subdirectory(mpi)
endif(MPI_SUPPORT)

# Instruction to enable the XMP support for POP-C++
if(XMP_SUPPORT)
  message(STATUS "XMP Support for POP-C++ is enable")
  add_subdirectory(xmp)
endif(XMP_SUPPORT)


# Add target to clean the distribution of all CMake generated files
IF (UNIX)
  ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   CMakeFiles
   cmake.check_cache
   *.cmake
   interconnector/Makefile
   interconnector/*.cmake
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
   include/Makefile
   include/*.cmake
   include/CMakeFiles  
   config.h
   Makefile
   *~
  )
  
  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -Rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean
  )
ENDIF(UNIX)
