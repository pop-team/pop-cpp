include_directories(${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_custom_command(OUTPUT popc_mpi_interconnector.tmp
                   COMMAND ${MPI_COMPILER} ${MPI_COMPILER_FLAGS} popc_mpi_interconnector popc_mpi_interconnector.cpp -I${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/lib/libpopc_common.a
                   DEPENDS popc_mpi_interconnector.cpp
                   COMMENT "MPI Compilation of POP-C++ MPI Interconnector")

add_custom_command(OUTPUT openmpi_check_support.tmp
                   COMMAND ${MPI_COMPILER} ${MPI_COMPILER_FLAGS} openmpi_check_support openmpi_check_support.cpp -I${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/lib/libpopc_common.a
                   DEPENDS openmpi_check_support.cpp
                   COMMENT "MPI Compilation of POP-C++ MPI Thread Level test")

                   
add_custom_target(popc_mpi_interconnector ALL DEPENDS popc_mpi_interconnector.tmp)                 
add_custom_target(openmpi_check_support ALL DEPENDS openmpi_check_support.tmp)                   
                   
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "openmpi_check_support;popc_mpi_interconnector")