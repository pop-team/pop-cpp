#
# POP-C++ 
# MPI Communication layer components
# 
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

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
                   
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "openmpi_check_support;popc_mpi_interconnector")


# Install programs in the mpi directory of the installation path
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_mpi_interconnector DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/openmpi_check_support DESTINATION mpi)
