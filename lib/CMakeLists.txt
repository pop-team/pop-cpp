#
# POP-C++ 
# Common library build process
# 
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

include_directories(${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_OUTPUT_EXTENION ".o")

add_library(popc_common
accesspoint.cc
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
popc_buffer_xdr_mpi.cpp
combox.cc
combox_factory.cc
combox_socket.cc
event.cc
exception.cc
explorationList.cc
explorationList.h.gch
interface.cc
memspool.cc
mutex.cc
object.cc
od.cc
popwayback.cc
popc_combox_uds.cpp
popc_connection_uds.cpp
string.cc
system.cc
thread.cc
timer.cc
utils.cc
popc_allocator_factory.cpp
popc_allocator_uds_interconnector.cpp
popc_allocator_tcpip.cpp
)

SET (POPCCOMMON -Wl,-ldl -Wl,-lpthread)

TARGET_LINK_LIBRARIES(popc_common ${POPCCOMMON})

add_custom_command(OUTPUT paroc_infmain.std.o
                   COMMAND ${CMAKE_CXX_COMPILER} ${POPC_MAIN_FLAGS} paroc_infmain.std.cc -I${CMAKE_SOURCE_DIR}/include
                   DEPENDS paroc_infmain.std.cc
                   COMMENT "Compile POP-C++ Master main")
                   
add_custom_command(OUTPUT paroc_objmain.std.o
                   COMMAND ${CMAKE_CXX_COMPILER} ${POPC_MAIN_FLAGS} paroc_objmain.std.cc -I${CMAKE_SOURCE_DIR}/include
                   DEPENDS paroc_objmain.std.cc
                   COMMENT "Compile POP-C++ Object main")                   
                   
add_custom_target(popcpp_object_main ALL DEPENDS paroc_objmain.std.o) 
add_custom_target(popcpp_master_main ALL DEPENDS paroc_infmain.std.o) 

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_infmain.std.o DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_objmain.std.o DESTINATION lib)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_common.a DESTINATION lib)

