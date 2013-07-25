#
# POP-C++ 
# services components
# 
# AUTHOR: vanhieu.nguyen
# DATE: 2013/07/17
#

set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)

set(POPCPP_Object_COMPILER_FLAGS -object -o)
set(POPCPP_COMPILER_FLAGS -o)
set(POPCPP_Parclass_COMPILER_FLAGS -c -o)

set(POPCPP_FLAGS -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp)

set(POPCPP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include/dynamic)
set(POPCPP_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/dynamic)

include_directories(${CMAKE_SOURCE_DIR}/ ${POPCPP_INCLUDE_PATH})
link_directories(${CMAKE_SOURCE_DIR}/lib/dynamic)

#compilation for popfilemanager
add_custom_command(OUTPUT popfilemanager_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} popfilemanager_obj.o popfilemanager_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS popfilemanager_obj.cc
                  )

add_custom_target(popfilemanager ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} popfilemanager popfilemanager_obj.o
-L${POPCPP_LIB_PATH} ${POPCPP_LIB_PATH}/libpopc_service_common.a
                  DEPENDS popfilemanager_obj.o
                  )

#compilation for popc_search_node
add_custom_command(OUTPUT popc_search_node_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} popc_search_node_obj.o popc_search_node_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS popc_search_node_obj.cc
                  )

add_custom_target(popc_search_node ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} popc_search_node popc_search_node_obj.o
-L${POPCPP_LIB_PATH} ${POPCPP_LIB_PATH}/libpopc_service_common.a
                  DEPENDS popc_search_node_obj.o
                  )

#compilation for jobmgr
add_custom_command(OUTPUT jobmgr_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} jobmgr_obj.o jobmgr_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS jobmgr_obj.cc
                  )

add_custom_target(jobmgr ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} jobmgr jobmgr_obj.o
-L${POPCPP_LIB_PATH} ${POPCPP_LIB_PATH}/libpopc_service_common.a
                  DEPENDS jobmgr_obj.o
                  )

#compilation for appservice
add_custom_command(OUTPUT appservice_obj.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS}  appservice_obj.o appservice_obj.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS appservice_obj.cc
                  )

add_custom_target(appservice ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS} appservice appservice_obj.o
-L${POPCPP_LIB_PATH} ${POPCPP_LIB_PATH}/libpopc_service_common.a
                  DEPENDS appservice_obj.o
                  )


#compilation for localservice_launcher
add_custom_command(OUTPUT localservice_launcher.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} localservice_launcher.o localservice_launcher.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS localservice_launcher.cc
                  )

add_custom_target(localservice_launcher ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_COMPILER_FLAGS} localservice_launcher localservice_launcher.o
-L${POPCPP_LIB_PATH} ${POPCPP_LIB_PATH}/libpopc_service_common.a
                  DEPENDS localservice_launcher.o
                  )

#compilation for jobmgr_launcher
add_custom_command(OUTPUT jobmgr_launcher.o
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS} jobmgr_launcher.o jobmgr_launcher.cc
-I${POPCPP_LIB_PATH}
                  DEPENDS jobmgr_launcher.cc
                  )

add_custom_target(jobmgr_launcher ALL
                  COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_COMPILER_FLAGS} jobmgr_launcher jobmgr_launcher.o
-L${POPCPP_LIB_PATH} ${POPCPP_LIB_PATH}/libpopc_service_common.a
                  DEPENDS jobmgr_launcher.o
                  )

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "popc_search_node;jobmgr;appservice;localservice_launcher;jobmgr_launcher;popfilemanager")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun.in ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun)

# Install programs in the mpi directory of the installation path
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_search_node DESTINATION services)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr DESTINATION services)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/appservice DESTINATION services)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/localservice_launcher DESTINATION services)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr_launcher DESTINATION services)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popfilemanager DESTINATION services)

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun DESTINATION services)

