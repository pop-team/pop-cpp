#
# POP-C++ 
# services components
# 
# AUTHOR: vanhieu.nguyen
# DATE: 2013/07/17
#

if(NOT DEFINED POPCPP_SERVICES_COMPILER_FLAGS)
  set(POPCPP_SERVICES_COMPILER_FLAGS -noclean -object -o)
endif(NOT DEFINED POPCPP_SERVICES_COMPILER_FLAGS)

set(POPCPP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include/dynamic)
set(POPCPP_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/dynamic)
include_directories(${CMAKE_SOURCE_DIR}/ ${POPCPP_INCLUDE_PATH})
link_directories(${CMAKE_SOURCE_DIR}/lib/dynamic)

set (CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)

#add_custom_target(popc_search_node ALL
#                  COMMAND ${CMAKE_CXX_COMPILER} ${POPCPP_SERVICES_COMPILER_FLAGS} popc_search_node popc_search_node.cc
#-I${POPCPP_INCLUDE_PATH} ${POPCPP_LIB_PATH}/libpopc_services_common.a
#                  DEPENDS popc_search_node.cc
#                  )

#add_custom_target(jobmgr ALL
#                  COMMAND ${CMAKE_CXX_COMPILER} ${POPCPP_SERVICES_COMPILER_FLAGS} jobmgr jobmgr_obj.cc
#-I${POPCPP_INCLUDE_PATH} ${POPCPP_LIB_PATH}/libpopc_services_common.a
#                  DEPENDS jobmgr_obj.cc
#                  )

#add_custom_target(appservice ALL
#                  COMMAND ${CMAKE_CXX_COMPILER} ${POPCPP_SERVICES_COMPILER_FLAGS} appservice appservice_obj.cc
#-I${POPCPP_INCLUDE_PATH} ${POPCPP_LIB_PATH}/libpopc_services_common.a
#                  DEPENDS appservice_obj.cc
#                  )

add_custom_target(localservice_launcher ALL
                  COMMAND ${CMAKE_CXX_COMPILER} ${POPCPP_SERVICES_COMPILER_FLAGS} localservice_launcher localservice_launcher.cc
-I${POPCPP_INCLUDE_PATH} ${POPCPP_LIB_PATH}/libpopc_services_common.a
                  DEPENDS localservice_launcher.cc
                  )

#add_custom_target(jobmgr_launcher ALL
#                  COMMAND ${CMAKE_CXX_COMPILER} ${POPCPP_SERVICES_COMPILER_FLAGS} jobmgr_launcher jobmgr_launcher.cc
#-I${POPCPP_INCLUDE_PATH} ${POPCPP_LIB_PATH}/libpopc_services_common.a
#                  DEPENDS jobmgr_launcher.cc
#                  )

#add_custom_target(popfilemanager ALL
#                  COMMAND ${CMAKE_CXX_COMPILER} ${POPCPP_SERVICES_COMPILER_FLAGS} popfilemanager popfilemanager_obj.cc
#-I${POPCPP_INCLUDE_PATH} ${POPCPP_LIB_PATH}/libpopc_services_common.a
#                  DEPENDS popfilemanager_obj.cc
#                  )

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "popc_search_node;jobmgr;appservice;localservice_launcher;jobmgr_launcher;popfilemanager")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun.in ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun)

# Install programs in the mpi directory of the installation path
#install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_search_node DESTINATION services)
#install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr DESTINATION services)
#install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/appservice DESTINATION services)
#install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/localservice_launcher DESTINATION services)
#install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr_launcher DESTINATION services)
#install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popfilemanager DESTINATION services)

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun DESTINATION services)

