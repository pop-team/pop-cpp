include_directories(${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/include)

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
string.cc
system.cc
testplugin.cc
thread.cc
timer.cc
utils.cc
)

SET (POPCCOMMON -Wl,-ldl -Wl,-lpthread)

TARGET_LINK_LIBRARIES(popc_common ${POPCCOMMON})

add_library(popc_main
  paroc_infmain.std.cc
  )
  
add_library(popc_objmain  
  paroc_objmain.std.cc 
  )


