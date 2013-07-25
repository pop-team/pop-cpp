#
# POP-C++ 
# services components
# 
# AUTHOR: vanhieu.nguyen
# DATE: 2013/07/25
#

set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)

set(POPCPP_Object_COMPILER_FLAGS -object -o)
set(POPCPP_COMPILER_FLAGS -o)
set(POPCPP_ParclassForService_COMPILER_FLAGS -c -o)

set(POPCPP_FLAGS -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp)

set(POPCPP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include/dynamic)
set(POPCPP_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/dynamic)

set(POPCPP_LIB_INSTALL lib/dynamic)
set(POPCPP_SERVICES_INSTALL services)

include_directories(${CMAKE_SOURCE_DIR}/ ${POPCPP_INCLUDE_PATH})
link_directories(${CMAKE_SOURCE_DIR}/lib/dynamic)


#BUILD .ph file
#paroc_service_base.ph
add_custom_command(OUTPUT paroc_service_base.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} paroc_service_base.ph.stub.o paroc_service_base.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS paroc_service_base.ph
		   )

#jobmgr.ph
add_custom_command(OUTPUT jobmgr.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} jobmgr.ph.stub.o jobmgr.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS jobmgr.ph
		   )

#popc_search_node.ph
add_custom_command(OUTPUT popc_search_node.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popc_search_node.ph.stub.o popc_search_node.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_search_node.ph
		   )

#codemgr.ph
add_custom_command(OUTPUT codemgr.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} codemgr.ph.stub.o codemgr.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS codemgr.ph
		   )

#remotelog.ph
add_custom_command(OUTPUT remotelog.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} remotelog.ph.stub.o remotelog.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS remotelog.ph
		   )

#objectmonitor.ph
add_custom_command(OUTPUT objectmonitor.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} objectmonitor.ph.stub.o objectmonitor.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS objectmonitor.ph
		   )

#batchmgr.ph
add_custom_command(OUTPUT batchmgr.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} batchmgr.ph.stub.o batchmgr.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS batchmgr.ph
		   )

#appservice.ph
add_custom_command(OUTPUT appservice.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} appservice.ph.stub.o appservice.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS appservice.ph
		   )


#popfilemanager.ph
add_custom_command(OUTPUT popfilemanager.ph.stub.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popfilemanager.ph.stub.o popfilemanager.ph
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popfilemanager.ph
		   )

add_custom_target(aaparoc_stub_services ALL DEPENDS paroc_service_base.ph.stub.o jobmgr.ph.stub.o popc_search_node.ph.stub.o codemgr.ph.stub.o remotelog.ph.stub.o objectmonitor.ph.stub.o appservice.ph.stub.o batchmgr.ph.stub.o popfilemanager.ph.stub.o)


#popc_logger.cpp
add_custom_command(OUTPUT popc_logger.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popc_logger.o popc_logger.cpp
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_logger.cpp)

#service_base.cc
add_custom_command(OUTPUT service_base.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} service_base.o service_base.cc 
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS service_base.cc")

#jobmgr.cc
add_custom_command(OUTPUT jobmgr.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} jobmgr.o jobmgr.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS jobmgr.cc")

#popc_search_node.cc
add_custom_command(OUTPUT popc_search_node.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popc_search_node.o popc_search_node.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popc_search_node.cc")

#codemgr.cc
add_custom_command(OUTPUT codemgr.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} codemgr.o codemgr.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS codemgr.cc)

#remotelog.cc
add_custom_command(OUTPUT remotelog.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} remotelog.o remotelog.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS remotelog.cc)

#objectmonitor.cc
add_custom_command(OUTPUT objectmonitor.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} objectmonitor.o objectmonitor.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS objectmonitor.cc)

#batchmgr.cc
add_custom_command(OUTPUT batchmgr.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} batchmgr.o batchmgr.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS batchmgr.cc)

#appservice.cc
#add_custom_command(OUTPUT appservice.o
#                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAG} appservice.o appservice.cc
#		  -I${POPCPP_INCLUDE_PATH}
#                  DEPENDS appservice.cc)

#popfilemanager.cc
add_custom_command(OUTPUT popfilemanager.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popfilemanager.o popfilemanager.cc
		  -I${POPCPP_INCLUDE_PATH}
                  DEPENDS popfilemanager.cc)


add_custom_command(OUTPUT libpopc_services.a
                  COMMAND ar cru libpopc_services.a service_base.o jobmgr.o popc_search_node.o codemgr.o remotelog.o objectmonitor.o appservice.o batchmgr.o popfilemanager.o popc_logger.o paroc_service_base.ph.stub.o jobmgr.ph.stub.o popc_search_node.ph.stub.o codemgr.ph.stub.o remotelog.ph.stub.o objectmonitor.ph.stub.o appservice.ph.stub.o batchmgr.ph.stub.o popfilemanager.ph.stub.o
		  DEPENDS service_base.o jobmgr.o popc_search_node.o codemgr.o remotelog.o objectmonitor.o appservice.o batchmgr.o popfilemanager.o popc_logger.o paroc_service_base.ph.stub.o jobmgr.ph.stub.o popc_search_node.ph.stub.o codemgr.ph.stub.o remotelog.ph.stub.o objectmonitor.ph.stub.o appservice.ph.stub.o batchmgr.ph.stub.o popfilemanager.ph.stub.o
		  COMMENT "Compile POP-C++ generated lib for popc_services")

add_custom_target(abpopc_services ALL DEPENDS service_base.o jobmgr.o popc_search_node.o codemgr.o remotelog.o objectmonitor.o batchmgr.o appservice.o popfilemanager.o popc_logger.o paroc_service_base.ph.stub.o jobmgr.ph.stub.o popc_search_node.ph.stub.o codemgr.ph.stub.o remotelog.ph.stub.o objectmonitor.ph.stub.o appservice.ph.stub.o batchmgr.ph.stub.o popfilemanager.ph.stub.o libpopc_services.a)

#compilation for popfilemanager
add_custom_command(OUTPUT popfilemanager_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popfilemanager_obj.o popfilemanager_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS popfilemanager_obj.cc
                  )

add_custom_target(popfilemanager ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} popfilemanager popfilemanager_obj.o
-L${POPCPP_LIB_PATH} libpopc_services.a
                  DEPENDS popfilemanager_obj.o
                  )

#compilation for popc_search_node
add_custom_command(OUTPUT popc_search_node_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} popc_search_node_obj.o popc_search_node_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS popc_search_node_obj.cc
                  )

add_custom_target(popc_search_node ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} popc_search_node popc_search_node_obj.o
-L${POPCPP_LIB_PATH} libpopc_services.a
                  DEPENDS popc_search_node_obj.o
                  )

#compilation for jobmgr
add_custom_command(OUTPUT jobmgr_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} jobmgr_obj.o jobmgr_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS jobmgr_obj.cc
                  )

add_custom_target(jobmgr ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} jobmgr jobmgr_obj.o
-L${POPCPP_LIB_PATH} libpopc_services.a
                  DEPENDS jobmgr_obj.o
                  )

#compilation for appservice
add_custom_command(OUTPUT appservice_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS}  appservice_obj.o appservice_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS appservice_obj.cc
                  )

add_custom_target(appservice ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} appservice appservice_obj.o
-L${POPCPP_LIB_PATH} libpopc_services.a
                  DEPENDS appservice_obj.o
                  )


#compilation for localservice_launcher
add_custom_command(OUTPUT localservice_launcher.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} localservice_launcher.o localservice_launcher.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS localservice_launcher.cc
                  )

add_custom_target(localservice_launcher ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_COMPILER_FLAGS} localservice_launcher localservice_launcher.o
-L${POPCPP_LIB_PATH} libpopc_services.a
                  DEPENDS localservice_launcher.o
                  )

#compilation for jobmgr_launcher
add_custom_command(OUTPUT jobmgr_launcher.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS} jobmgr_launcher.o jobmgr_launcher.cc
-I${POPCPP_LIB_PATH} -I${CMAKE_SOURCE_DIR}
                  DEPENDS jobmgr_launcher.cc
                  )

add_custom_target(jobmgr_launcher ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_COMPILER_FLAGS} jobmgr_launcher jobmgr_launcher.o
-L${POPCPP_LIB_PATH} libpopc_services.a
                  DEPENDS jobmgr_launcher.o
                  )

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "popc_search_node;jobmgr;appservice;localservice_launcher;jobmgr_launcher;popfilemanager")

# Install programs in the mpi directory of the installation path
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_search_node DESTINATION ${POPCPP_SERVICES_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr DESTINATION ${POPCPP_SERVICES_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/appservice DESTINATION ${POPCPP_SERVICES_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/localservice_launcher DESTINATION ${POPCPP_SERVICES_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr_launcher DESTINATION ${POPCPP_SERVICES_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popfilemanager DESTINATION ${POPCPP_SERVICES_INSTALL})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_services.a DESTINATION ${POPCPP_LIB_INSTALL})

