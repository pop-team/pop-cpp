cmake_minimum_required(VERSION 2.6)

project(POPCPP)

include(CheckIncludeFile)
include(CheckLibraryExists)

find_package(Threads)

set(CMAKE_INSTALL_PREFIX "/Users/clementval/popc")

#check_include_file(dlfcn.h HAVE_DLFCN_H)
#check_library_exists(dl dlclose "" HAVE_LIBDL)

# Define variable for MPI compilation
set(MPI_COMPILER mpic++)
set(MPI_COMPILER_FLAGS -o)

# Define version of POP-C++ - It will be shown on the compiler usage message and with -version option
set(VERSION "2.6.3 - K Computer")
execute_process(COMMAND uname -m OUTPUT_VARIABLE HOST_CPU_RAW)
string(REGEX REPLACE "\n" "" HOST_CPU ${HOST_CPU_RAW})
execute_process(COMMAND uname -s OUTPUT_VARIABLE HOST_KERNEL_RAW)
string(REGEX REPLACE "\n" "" HOST_KERNEL ${HOST_KERNEL_RAW})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

# Add subdirectory which inlude a CMakeLists.text file
add_subdirectory(lib)
add_subdirectory(interconnector)


install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/paroc_infmain.std.o DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/paroc_objmain.std.o DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libpopc_common.a DESTINATION lib)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/interconnector/popc_mpi_interconnector DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/interconnector/openmpi_check_support DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/parser/popcc DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/parser/popcpp DESTINATION bin)


IF (UNIX)
  ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   CMakeFiles
   cmake.check_cache
   *.cmake
   Makefile
   core core.*
   gmon.out
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
