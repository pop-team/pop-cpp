#
# POP-C++
# Common (pseudo-dynamic) library build process
#
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

include_directories(${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/include/pseudodynamic ${MPI_INCLUDE_PATH})

include(CMakeForceCompiler)

set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

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
    string.cc
    system.cc
    thread.cc
    timer.cc
    utils.cc
    popwayback.cc
)

SET (POPCCOMMON -Wl,-ldl -Wl,-lpthread)

TARGET_LINK_LIBRARIES(popc_common_psdyn ${POPCCOMMON})

add_custom_command(
    OUTPUT paroc_infmain.psdyn.o
    COMMAND ${MPI_CXX_COMPILER} ${POPC_MAIN_FLAGS} paroc_infmain.psdyn.cc -I${CMAKE_SOURCE_DIR}/include/pseudodynamic
    DEPENDS paroc_infmain.psdyn.cc
    COMMENT "Compile POP-C++ Master main")

add_custom_command(
    OUTPUT popc_objmain.psdyn.o
    COMMAND ${MPI_CXX_COMPILER} ${POPC_MAIN_FLAGS} popc_objmain.psdyn.cc -I${CMAKE_SOURCE_DIR}/include/pseudodynamic
    DEPENDS popc_objmain.psdyn.cc
    COMMENT "Compile POP-C++ Object main")

add_custom_target(popcpp_object_psdyn_main ALL DEPENDS popc_objmain.psdyn.o)
add_custom_target(popcpp_master_psdyn_main ALL DEPENDS paroc_infmain.psdyn.o)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_infmain.psdyn.o DESTINATION lib/pseudodynamic)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_objmain.psdyn.o DESTINATION lib/pseudodynamic)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_common_psdyn.a DESTINATION lib/pseudodynamic)
