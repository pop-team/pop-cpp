#
# POP-C++ 
# Common (dynamic) library build process
# 
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

set(POPCPP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include/dynamic)

set(POPCC_INCLUDE_INSTALL include/dynamic)
set(POPCC_LIB_INSTALL lib/dynamic)

include_directories(${CMAKE_SOURCE_DIR}/ ${POPCPP_INCLUDE_PATH})

set(CMAKE_CXX_OUTPUT_EXTENION ".o")

set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)
set(POPCPP_FLAGS -cxxmain -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp -cxx=g++)

set(POPCPP_Parclass_COMPILER_FLAGS -parclass-nobroker -c -o)
set(POPCPP_ParclassForService_COMPILER_FLAGS -c -o)

add_library(popc_common
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
popc_buffer_xdr_mpi.cpp
combox.cc
combox_factory.cc
combox_socket.cc
debug.cc
event.cc
exception.cc
explorationList.cc
memspool.cc
mutex.cc
od.cc
popc_combox_uds.cpp
popc_connection_uds.cpp
popwayback.cc
string.cc
thread.cc
timer.cc
popc_allocator_factory.cpp
popc_allocator_uds_interconnector.cpp
popc_allocator_tcpip_ssh.cpp
popc_allocator_mpi_pseudo.cpp
)

SET (POPCCOMMON -Wl,-ldl -Wl,-lpthread)


TARGET_LINK_LIBRARIES(popc_common ${POPCCOMMON})


add_custom_command(OUTPUT paroc_infmain.std.o
                   COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} paroc_infmain.std.o paroc_infmain.std.cc 
		   -I${POPCPP_INCLUDE_PATH}
                   DEPENDS paroc_infmain.std.cc
                   COMMENT "Compile POP-C++ Master main")
                   
add_custom_command(OUTPUT paroc_objmain.std.o
                   COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} paroc_objmain.std.o paroc_objmain.std.cc 
		   -I${POPCPP_INCLUDE_PATH}
                   DEPENDS paroc_objmain.std.cc
                   COMMENT "Compile POP-C++ Object main")  
                  
add_custom_target(popcpp_object_main ALL DEPENDS paroc_objmain.std.o) 
add_custom_target(popcpp_master_main ALL DEPENDS paroc_infmain.std.o) 

#BUILD .ph file
#paroc_service_base.ph
add_custom_command(OUTPUT paroc_service_base.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} paroc_service_base.ph.stub_client.o paroc_service_base.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS paroc_service_base.ph
		  )

#jobmgr.ph
add_custom_command(OUTPUT jobmgr.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} jobmgr.ph.stub_client.o jobmgr.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS jobmgr.ph
		   )

#popc_search_node.ph
add_custom_command(OUTPUT popc_search_node.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} popc_search_node.ph.stub_client.o popc_search_node.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_search_node.ph
		   )

#codemgr.ph
add_custom_command(OUTPUT codemgr.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} codemgr.ph.stub_client.o codemgr.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS codemgr.ph
		   )

#remotelog.ph
add_custom_command(OUTPUT remotelog.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} remotelog.ph.stub_client.o remotelog.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS remotelog.ph
		   )

#objectmonitor.ph
add_custom_command(OUTPUT objectmonitor.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} objectmonitor.ph.stub_client.o objectmonitor.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS objectmonitor.ph
		   )

#batchmgr.ph
add_custom_command(OUTPUT batchmgr.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} batchmgr.ph.stub_client.o batchmgr.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS batchmgr.ph
		   )

#appservice.ph
add_custom_command(OUTPUT appservice.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} appservice.ph.stub_client.o appservice.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS appservice.ph
		   )


#popfilemanager.ph
add_custom_command(OUTPUT popfilemanager.ph.stub_client.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} popfilemanager.ph.stub_client.o popfilemanager.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popfilemanager.ph
		   )

add_custom_target(paroc_stub_parclass ALL DEPENDS paroc_service_base.ph.stub_client.o jobmgr.ph.stub_client.o popc_search_node.ph.stub_client.o codemgr.ph.stub_client.o remotelog.ph.stub_client.o objectmonitor.ph.stub_client.o appservice.ph.stub_client.o batchmgr.ph.stub_client.o popfilemanager.ph.stub_client.o)


#popc_logger.cpp
add_custom_command(OUTPUT popc_logger.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popc_logger.o popc_logger.cpp
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_logger.cpp)

add_custom_command(OUTPUT benchmark.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} benchmark.o benchmark.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS benchmark.cc)

add_custom_command(OUTPUT nodethread.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} nodethread.o nodethread.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS nodethread.cc)


add_custom_command(OUTPUT popc_search_node_info.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popc_search_node_info.o popc_search_node_info.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_search_node_info.cc)

add_custom_command(OUTPUT response.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} response.o response.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS response.cc)

add_custom_command(OUTPUT request.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} request.o request.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS request.cc)

add_custom_command(OUTPUT utils.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} utils.o utils.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS utils.cc)

add_custom_command(OUTPUT object.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} object.o object.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS object.cc)

add_custom_command(OUTPUT system.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} system.o system.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS system.cc)

add_custom_command(OUTPUT interface.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} interface.o interface.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS interface.cc)

add_custom_command(OUTPUT popc_allocator_tcpip_local.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popc_allocator_tcpip_local.o popc_allocator_tcpip_local.cpp
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_allocator_tcpip_local.cpp)

add_custom_command(OUTPUT libpopc_common.a
                  COMMAND ar r libpopc_common.a benchmark.o nodethread.o popc_logger.o popc_search_node_info.o response.o request.o utils.o object.o system.o interface.o popc_allocator_tcpip_local.o paroc_service_base.ph.stub_client.o jobmgr.ph.stub_client.o popc_search_node.ph.stub_client.o codemgr.ph.stub_client.o remotelog.ph.stub_client.o objectmonitor.ph.stub_client.o appservice.ph.stub_client.o batchmgr.ph.stub_client.o popfilemanager.ph.stub_client.o
		  DEPENDS benchmark.o nodethread.o popc_logger.o popc_search_node_info.o response.o request.o utils.o object.o system.o interface.o popc_allocator_tcpip_local.o paroc_service_base.ph.stub_client.o jobmgr.ph.stub_client.o popc_search_node.ph.stub_client.o codemgr.ph.stub_client.o remotelog.ph.stub_client.o objectmonitor.ph.stub_client.o appservice.ph.stub_client.o batchmgr.ph.stub_client.o popfilemanager.ph.stub_client.o
		  COMMENT "Compile POP-C++ generated lib for popc_common")


add_custom_target(popc_common_link ALL DEPENDS libpopc_common.a benchmark.o nodethread.o popc_logger.o popc_search_node_info.o response.o request.o utils.o)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/appservice.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/batchmgr.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/codemgr.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/objectmonitor.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_service_base.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_search_node.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popfilemanager.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/remotelog.ph DESTINATION ${POPCC_INCLUDE_INSTALL})
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/paroc_infmain.std.o DESTINATION ${POPCC_LIB_INSTALL})
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/paroc_objmain.std.o DESTINATION ${POPCC_LIB_INSTALL})
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_common.a DESTINATION ${POPCC_LIB_INSTALL})

