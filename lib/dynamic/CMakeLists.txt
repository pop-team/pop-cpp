#
# POP-C++ 
# Common (dynamic) library build process
# 
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

set(POPCPP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include/dynamic)

include_directories(${CMAKE_SOURCE_DIR}/ ${POPCPP_INCLUDE_PATH})

set(CMAKE_CXX_OUTPUT_EXTENION ".o")

set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)
set(POPCPP_FLAGS -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp)

set(POPCPP_Object_COMPILER_FLAGS -object -o)
set(POPCPP_Parclass_COMPILER_FLAGS -parclass-nobroker -c)
set(POPCPP_Parclass_COMPILER_FLAGS_TMP -c -o)

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
interface.cc
memspool.cc
mutex.cc
object.cc
od.cc
popc_combox_uds.cpp
popc_connection_uds.cpp
popwayback.cc
string.cc
system.cc
thread.cc
timer.cc
utils.cc
popc_allocator_factory.cpp
popc_allocator_uds_interconnector.cpp
popc_allocator_tcpip_local.cpp
popc_allocator_tcpip_ssh.cpp
popc_allocator_mpi_pseudo.cpp
)

SET (POPCCOMMON -Wl,-ldl -Wl,-lpthread)


TARGET_LINK_LIBRARIES(popc_common ${POPCCOMMON})

add_custom_command(OUTPUT paroc_infmain.std.o
                   COMMAND ${CMAKE_CXX_COMPILER} ${POPC_MAIN_FLAGS} paroc_infmain.std.cc -I${POPCPP_INCLUDE_PATH}
                   DEPENDS paroc_infmain.std.cc
                   COMMENT "Compile POP-C++ Master main")
                   
add_custom_command(OUTPUT paroc_objmain.std.o
                   COMMAND ${CMAKE_CXX_COMPILER} ${POPC_MAIN_FLAGS} paroc_objmain.std.cc -I${POPCPP_INCLUDE_PATH}
                   DEPENDS paroc_objmain.std.cc
                   COMMENT "Compile POP-C++ Object main")  
                  
add_custom_target(popcpp_object_main ALL DEPENDS paroc_objmain.std.o) 
add_custom_target(popcpp_master_main ALL DEPENDS paroc_infmain.std.o) 

#BUILD .ph file
add_custom_command(OUTPUT paroc_service_base.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS_TMP} paroc_service_base.stub.o paroc_service_base.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS paroc_service_base.ph
		   )

add_custom_command(OUTPUT jobmgr.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS_TMP} jobmgr.stub.o jobmgr.ph paroc_service_base.ph popc_search_node.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS jobmgr.ph paroc_service_base.ph popc_search_node.ph
		   )

add_custom_command(OUTPUT popc_search_node.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS_TMP} popc_search_node.stub.o popc_search_node.ph paroc_service_base.ph jobmgr.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_search_node.ph paroc_service_base.ph jobmgr.ph
		   )

#add_custom_command(OUTPUT codemgr.stub.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} codemgr.ph paroc_service_base.ph
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS codemgr.ph paroc_service_base.ph
#		   )

#add_custom_command(OUTPUT remotelog.stub.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} remotelog.ph paroc_service_base.stub.o
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS remotelog.ph paroc_service_base.stub.o
#		   )

#add_custom_command(OUTPUT objectmonitor.stub.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} objectmonitor.ph paroc_service_base.ph
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS objectmonitor.ph paroc_service_base.ph
#		   )

#add_custom_command(OUTPUT batchmgr.stub.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} batchmgr.ph paroc_service_base.ph
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS batchmgr.ph paroc_service_base.ph
#		   )

#add_custom_command(OUTPUT appservice.stub.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} appservice.ph codemgr.ph remotelog.ph objectmonitor.ph batchmgr.ph
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS appservice.ph codemgr.ph remotelog.ph objectmonitor.ph batchmgr.ph
#		   )


#add_custom_command(OUTPUT popfilemanager.stub.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} popfilemanager.ph paroc_service_base.ph
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS popfilemanager.ph paroc_service_base.ph
#		   )

#add_custom_target(paroc_stub_parclass ALL DEPENDS paroc_service_base.stub.o jobmgr.stub.o popc_search_node.stub.o codemgr.stub.o remotelog.stub.o objectmonitor.stub.o appservice.stub.o batchmgr.stub.o popfilemanager.stub.o)

add_custom_target(paroc_stub_parclass ALL DEPENDS paroc_service_base.stub.o jobmgr.stub.o popc_search_node.stub.o)

#add_custom_command(OUTPUT service_base.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} service_base.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} service_base.cc #paroc_service_base.stub.o objectmonitor.stub.o 
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS service_base.cc paroc_service_base.stub.o objectmonitor.stub.o
#		  COMMENT "Compile POP-C++ service base")

#add_custom_command(OUTPUT jobmgr.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} jobmgr.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} jobmgr.cc #codemgr.stub.o jobmgr.stub.o appservice.stub.o
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS jobmgr.cc codemgr.stub.o jobmgr.stub.o appservice.stub.o
#		  COMMENT "Compile POP-C++ jobmanager")

add_custom_command(OUTPUT popc_search_node.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS_TMP} popc_search_node.o popc_search_node.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_search_node.cc
		  COMMENT "Compile POP-C++ popcsearchnode")

#add_custom_command(OUTPUT codemgr.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} codemgr.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} codemgr.cc #codemgr.stub.o
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS codemgr.cc codemgr.stub.o
#		  COMMENT "Compile POP-C++ codemanager")

#add_custom_command(OUTPUT remotelog.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} remotelog.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} remotelog.cc #remotelog.stub.o appservice.stub.o 
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS remotelog.cc remotelog.stub.o appservice.stub.o
#		  COMMENT "Compile POP-C++ remotelog")

#add_custom_command(OUTPUT objectmonitor.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} objectmonitor.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} #objectmonitor.cc objectmonitor.stub.o
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS objectmonitor.cc objectmonitor.stub.o
#		  COMMENT "Compile POP-C++ objectmonitor")

#add_custom_command(OUTPUT appservice.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} appservice.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} appservice.cc #appservice.stub.o jobmgr.stub.o 
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS appservice.cc appservice.stub.o jobmgr.stub.o
#		  COMMENT "Compile POP-C++ appservice")

#add_custom_command(OUTPUT batchmgr.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} batchmgr.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} batchmgr.cc #batchmgr.stub.o
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS batchmgr.cc batchmgr.stub.o
#		  COMMENT "Compile POP-C++ batchmanager")

#add_custom_command(OUTPUT popfilemanager.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} popfilemanager.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} #popfilemanager.cc popc_search_node.stub.o popfilemanager.stub.o
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS popfilemanager.cc popc_search_node.stub.o popfilemanager.stub.o
#		  COMMENT "Compile POP-C++ popfilemanager")

#add_custom_command(OUTPUT popc_logger.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_Object_COMPILER_FLAGS} popc_logger.o ${POPCPP_Parclass_COMPILER_FLAGS} ${POPCPP_FLAGS} popc_logger.cpp
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS popc_logger.cpp
#		  COMMENT "Compile POP-C++ poplogger")

#add_custom_command(OUTPUT libpopc_services_common.a
#                  COMMAND ar rvs libpopc_services_common.a service_base.o jobmgr.o popc_search_node.o codemgr.o remotelog.o objectmonitor.o appservice.o batchmgr.o #popfilemanager.o popc_logger.o
#		  COMMENT "Compile POP-C++ generated lib for popc_service_common")
add_custom_command(OUTPUT libpopc_services_common.a
                  COMMAND ar rvs libpopc_services_common.a popc_search_node.o popc_search_node.stub.o
		  DEPENDS popc_search_node.o popc_search_node.stub.o
		  COMMENT "Compile POP-C++ generated lib for popc_service_common")


#add_custom_target(popc_services_common ALL DEPENDS service_base.o jobmgr.o popc_search_node.o codemgr.o remotelog.o objectmonitor.o appservice.o batchmgr.o popfilemanager.o popc_logger.o libpopc_services_common.a)

add_custom_target(popc_services_common ALL DEPENDS popc_search_node.o libpopc_services_common.a)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/appservice.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/batchmgr.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/codemgr.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/objectmonitor.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_service_base.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_search_node.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popcfilemanager.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/remotelog.ph DESTINATION ${POPCPP_INCLUDE_PATH})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_infmain.std.o DESTINATION lib/dynamic)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/paroc_objmain.std.o DESTINATION lib/dynamic)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_common.a DESTINATION lib/dynamic)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_services_common.a DESTINATION lib/dynamic)

