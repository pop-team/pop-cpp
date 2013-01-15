#
# POP-C++ 
# MPI Communication layer components
# 
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

if(NOT DEFINED POPCPP_MPI_COMPILER_FLAGS)
  set(POPCPP_MPI_COMPILER_FLAGS -o)
endif(NOT DEFINED POPCPP_MPI_COMPILER_FLAGS)

include_directories(${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_custom_target(popc_mpi_interconnector ALL
                  COMMAND ${MPI_CXX_COMPILER} ${POPCPP_MPI_COMPILER_FLAGS} popc_mpi_interconnector popc_mpi_interconnector.cpp
-I${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/lib/libpopc_common.a
-lpthread
                  DEPENDS popc_mpi_interconnector.cpp 
                  )


add_custom_target(openmpi_check_support ALL
                  COMMAND ${MPI_CXX_COMPILER} ${POPCPP_MPI_COMPILER_FLAGS} openmpi_check_support openmpi_check_support.cpp -I${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/lib/libpopc_common.a 
                  DEPENDS openmpi_check_support.cpp
                  )         

add_custom_target(popc_resource_manager_mpi ALL
                  COMMAND ${MPI_CXX_COMPILER} ${POPCPP_MPI_COMPILER_FLAGS} popc_resource_manager_mpi popc_resource_manager_mpi.cpp
                  DEPENDS popc_resource_manager_mpi.cpp
		  )

                   
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "openmpi_check_support;popc_mpi_interconnector;popc_resource_manager_mpi")


# Install programs in the mpi directory of the installation path
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_mpi_interconnector DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/openmpi_check_support DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_resource_manager_mpi DESTINATION mpi)
