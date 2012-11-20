cmake_minimum_required(VERSION 2.6)

#
# POP-C++ project. This CMakeLists.txt file is the entry point for the compilation of the POP-C++ library and services. 
#

project(POPCPP)

# Define version of POP-C++ - It will be shown on the compiler usage message and with -version option
set(VERSION "2.6.3 - K Computer")
execute_process(COMMAND uname -m OUTPUT_VARIABLE HOST_CPU_RAW)
string(REGEX REPLACE "\n" "" HOST_CPU ${HOST_CPU_RAW})
execute_process(COMMAND uname -s OUTPUT_VARIABLE HOST_KERNEL_RAW)
string(REGEX REPLACE "\n" "" HOST_KERNEL ${HOST_KERNEL_RAW})



include(CheckIncludeFile)
include(CheckLibraryExists)
find_package(Threads)

# Should be remove for release
set(CMAKE_INSTALL_PREFIX "/Users/clementval/popc")


# Check existence of header files and library 
#check_include_file(dlfcn.h HAVE_DLFCN_H)
#check_library_exists(dl dlclose "" HAVE_LIBDL)


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


# Install headers files, programs, library and object files
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/paroc_infmain.std.o DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/paroc_objmain.std.o DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libpopc_common.a DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/debug.h DESTINATION include)				
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_event.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_system.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/explorationList.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer_factory.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_exception.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_thread.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/request.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer_factory_finder.h DESTINATION include)	
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_interface.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_utils.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/response.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/nodethread.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer_raw.h DESTINATION include)	
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_list.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/popc_combox_uds.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/POPString.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer_raw_factory.h DESTINATION include)	
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_memspool.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/popc_logger.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/sysinfodef.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_accesspoint.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer_utils.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_mutex.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/timer.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_allocobj.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer_xdr.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_object.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/popc_search_node_info.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_array.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_buffer_xdr_factory.h DESTINATION include)	
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_od.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_base.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_combox.h DESTINATION include)			
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_broker.h	 DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_combox_factory.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_string.h	 DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/popwayback.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_broker_factory.h	DESTINATION include)	
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_combox_socket.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/paroc_sys.h DESTINATION include)		
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/priolist.h DESTINATION include)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/interconnector/popc_mpi_interconnector DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/interconnector/openmpi_check_support DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/parser/popcc DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/parser/popcpp DESTINATION bin)


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
   lib/Makefile
   lib/*.cmake   
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
