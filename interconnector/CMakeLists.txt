#
# POP-C++
# MPI Communication layer components
#
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

if(NOT DEFINED POPCPP_MPI_COMPILER_FLAGS)
    set(POPCPP_MPI_COMPILER_FLAGS -std=c++11 -o)
endif(NOT DEFINED POPCPP_MPI_COMPILER_FLAGS)

set(POPCPP_INTERCONNECTOR_INCLUDE_PATH "-I${CMAKE_SOURCE_DIR}/include/dynamic;-I${CMAKE_SOURCE_DIR}/include/core")
set(POPCPP_LIB -L${CMAKE_SOURCE_DIR}/lib/core;-L${CMAKE_SOURCE_DIR}/lib/dynamic;-L${CMAKE_SOURCE_DIR}/services/lib;-lpopc_core;-lpopc_common;-lpopc_core)
# include_directories(${CMAKE_SOURCE_DIR}/ ${POPCPP_INCLUDE_PATH})
# link_directories(${CMAKE_SOURCE_DIR}/lib/dynamic)

# Add more warnings
add_definitions(-Wall -Wextra)

add_custom_target(popc_mpi_interconnector ALL
    COMMAND ${MPI_CXX_COMPILER} ${POPCPP_MPI_COMPILER_FLAGS} popc_mpi_interconnector ${CMAKE_CURRENT_SOURCE_DIR}/popc_mpi_interconnector.cpp
        ${POPCPP_INTERCONNECTOR_INCLUDE_PATH} ${POPCPP_LIB} -lpthread
    DEPENDS popc_mpi_interconnector.cpp)

add_custom_target(openmpi_check_support ALL
    COMMAND ${MPI_CXX_COMPILER} ${POPCPP_MPI_COMPILER_FLAGS} openmpi_check_support ${CMAKE_CURRENT_SOURCE_DIR}/openmpi_check_support.cpp ${POPCPP_INTERCONNECTOR_INCLUDE_PATH}
        ${POPCPP_LIB}
    DEPENDS openmpi_check_support.cpp)

add_custom_target(popc_resource_manager_mpi ALL
    COMMAND ${MPI_CXX_COMPILER} ${POPCPP_MPI_COMPILER_FLAGS} popc_resource_manager_mpi ${CMAKE_CURRENT_SOURCE_DIR}/popc_resource_manager_mpi.cpp
    DEPENDS popc_resource_manager_mpi.cpp)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "openmpi_check_support;popc_mpi_interconnector;popc_resource_manager_mpi")

# Install programs in the mpi directory of the installation path
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_mpi_interconnector DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/openmpi_check_support DESTINATION mpi)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_resource_manager_mpi DESTINATION mpi)
