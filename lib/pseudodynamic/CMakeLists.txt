#
# POP-C++
# Common (pseudo-dynamic) library build process
#
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

include_directories(${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/include/pseudodynamic ${MPI_CXX_INCLUDE_PATH})

# include(CMakeForceCompiler)

set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

# Activate some warnings
add_definitions(-Wall -Wextra -Werror)

add_library(popc_common_psdyn
    accesspoint.cc
    allocobj.cc
    broker.cc
    broker_factory.cc
    broker_receive.cc
    broker_serve.cc
    buffer.cc
    buffer_factory.cc
    buffer_factory_finder.cc
    buffer_raw.cc
    buffer_raw_factory.cc
    buffer_utils.cc
    buffer_xdr.cc
    buffer_xdr_factory.cc
    combox.cc
    combox_factory.cc
    combox_socket.cc
    event.cc
    exception.cc
    interface.cc
    memspool.cc
    mutex.cc
    object.cc
    od.cc
    popc_combox_mpi.cc
    popc_connection_mpi.cpp
    popc_logger.cpp
    popwayback.cc
    string.cc
    system.cc
    thread.cc
    timer.cc
    popc_intface_linux.cc
    utils.cc
)

SET (POPCCOMMON -Wl,-ldl -Wl,-lpthread)

TARGET_LINK_LIBRARIES(popc_common_psdyn ${POPCCOMMON})

add_custom_command(
    OUTPUT paroc_infmain.psdyn.o
    COMMAND ${MPI_CXX_COMPILER} ${POPC_MAIN_FLAGS} paroc_infmain.psdyn.cc 
    -I${CMAKE_SOURCE_DIR}/include/pseudodynamic
    DEPENDS paroc_infmain.psdyn.cc
    COMMENT "Compile POP-C++ Master main")

add_custom_command(
    OUTPUT popc_objmain.psdyn.o
    COMMAND ${MPI_CXX_COMPILER} ${POPC_MAIN_FLAGS} popc_objmain.psdyn.cc 
    -I${CMAKE_SOURCE_DIR}/include/pseudodynamic
    DEPENDS popc_objmain.psdyn.cc
    COMMENT "Compile POP-C++ Object main")

add_custom_target(popcpp_object_psdyn_main ALL DEPENDS popc_objmain.psdyn.o)
add_custom_target(popcpp_master_psdyn_main ALL DEPENDS paroc_infmain.psdyn.o)

# Compile a cxx file into a .o
function(popcc_compile_cxx cxx_file)
add_custom_command(
    OUTPUT ${POPCC_OUTPUT_DIR}/${cxx_file}.o
    COMMAND ${POPCC_PARCLASS_SERVICE_COMMAND} ${POPCC_OUTPUT_DIR}/${cxx_file}.o ${cxx_file} -I${POPCPP_INCLUDE_PATH}
    DEPENDS ${cxx_file})
endfunction(popcc_compile_cxx)

# Note: We need to compile utils.cc here to enable the _POPC_ compilation flag
#popcc_compile_cxx(utils.cc)


# Build the interface (Win/Lin)

if(WIN32)
    set(intface_cc_file popc_intface_windows.cc)
    set(intface_o_file popc_intface_windows.o)
elseif(UNIX)
    set(intface_cc_file popc_intface_linux.cc)
    set(intface_o_file popc_intface_linux.o)
endif(WIN32)

add_custom_command(
    OUTPUT ${intface_o_file}
    COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} ${intface_o_file} ${intface_cc_file}
        -I${POPCPP_INCLUDE_PATH}
    DEPENDS ${intface_cc_file})

# Final link steps

add_custom_command(
    OUTPUT libpopc_common_psdyn.a
    COMMAND ar r libpopc_common_psdyn.a ${intface_o_file} ${POPCC_GENERATED_FILES}
    DEPENDS ${intface_o_file} ${POPCC_GENERATED_FILES}
    COMMENT "Compile POP-C++ generated lib for popc_common_psdyn")

#add_custom_target(
#    popc_common_link_psdyn ALL
#    DEPENDS libpopc_common_psdyn.a ${intface_o_file} ${POPCC_GENERATED_FILES})

# Install all the files

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_infmain.psdyn.o DESTINATION lib/pseudodynamic)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_objmain.psdyn.o DESTINATION lib/pseudodynamic)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_common_psdyn.a DESTINATION lib/pseudodynamic)
