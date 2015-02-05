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

set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

# Activate some warnings
add_definitions(-Wall -Wextra -Werror)

# Compile in C++11 mode
add_definitions(-std=c++11)

if(WIN32)
    set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc.exe)
    set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -cxxmain -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp.exe)
elseif(UNIX)
    set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)
    set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -cxxmain -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp)
endif(WIN32)

set(POPCPP_Parclass_COMPILER_FLAGS -parclass-nobroker -c -o)
set(POPCPP_ParclassForService_COMPILER_FLAGS -c -o)
set(POPCC_PARCLASS_COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS})
set(POPCC_PARCLASS_SERVICE_COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS})
set(POPCC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

add_library(popc_common
    accesspoint.cc
    allocobj.cc
    broker_factory.cc
    buffer.cc
    buffer_factory.cc
    buffer_factory_finder.cc
    buffer_raw.cc
    buffer_raw_factory.cc
    buffer_utils.cc
    buffer_xdr_factory.cc
    popc_buffer_xdr_mpi.cpp
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
    popc_allocator_mpi_pseudo.cpp
)

SET (POPCCOMMON -Wl,-ldl -Wl)

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

# Compile a .ph file into a .ph.stub_client.o
function(popcc_compile_ph ph_file)
add_custom_command(
    OUTPUT ${POPCC_OUTPUT_DIR}/${ph_file}.stub_client.o
    COMMAND ${POPCC_PARCLASS_COMMAND} ${POPCC_OUTPUT_DIR}/${ph_file}.stub_client.o ${ph_file} -I${POPCPP_INCLUDE_PATH}
    DEPENDS ${ph_file})
endfunction(popcc_compile_ph)

# Compile a cxx file into a .o
function(popcc_compile_cxx cxx_file)
add_custom_command(
    OUTPUT ${POPCC_OUTPUT_DIR}/${cxx_file}.o
    COMMAND ${POPCC_PARCLASS_SERVICE_COMMAND} ${POPCC_OUTPUT_DIR}/${cxx_file}.o ${cxx_file} -I${POPCPP_INCLUDE_PATH}
    DEPENDS ${cxx_file})
endfunction(popcc_compile_cxx)

# Build .ph files

popcc_compile_ph(paroc_service_base.ph)
popcc_compile_ph(jobmgr.ph)
popcc_compile_ph(popc_search_node.ph)
popcc_compile_ph(codemgr.ph)
popcc_compile_ph(remotelog.ph)
popcc_compile_ph(objectmonitor.ph)
popcc_compile_ph(batchmgr.ph)
popcc_compile_ph(appservice.ph)
popcc_compile_ph(popfilemanager.ph)

set(POPCC_GENERATED_STUBS
    ${POPCC_OUTPUT_DIR}/paroc_service_base.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/jobmgr.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/popc_search_node.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/codemgr.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/remotelog.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/objectmonitor.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/appservice.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/batchmgr.ph.stub_client.o
    ${POPCC_OUTPUT_DIR}/popfilemanager.ph.stub_client.o)

add_custom_target(paroc_stub_parclass ALL DEPENDS ${POPCC_GENERATED_STUBS})

# Build CXX files

popcc_compile_cxx(popc_logger.cpp)
popcc_compile_cxx(benchmark.cc)
popcc_compile_cxx(broker.cc)
popcc_compile_cxx(broker_receive.cc)
popcc_compile_cxx(broker_serve.cc)
popcc_compile_cxx(buffer_xdr.cc)
popcc_compile_cxx(combox.cc)
popcc_compile_cxx(combox_factory.cc)
popcc_compile_cxx(combox_socket.cc)
popcc_compile_cxx(nodethread.cc)
popcc_compile_cxx(popc_search_node_info.cc)
popcc_compile_cxx(response.cc)
popcc_compile_cxx(request.cc)
popcc_compile_cxx(utils.cc)
popcc_compile_cxx(object.cc)
popcc_compile_cxx(system.cc)
popcc_compile_cxx(interface.cc)
popcc_compile_cxx(popc_allocator_tcpip_local.cpp)
popcc_compile_cxx(popc_allocator_tcpip_ssh.cpp)

set(POPCC_GENERATED_FILES
    ${POPCC_OUTPUT_DIR}/benchmark.cc.o
    ${POPCC_OUTPUT_DIR}/broker.cc.o
    ${POPCC_OUTPUT_DIR}/broker_receive.cc.o
    ${POPCC_OUTPUT_DIR}/broker_serve.cc.o
    ${POPCC_OUTPUT_DIR}/buffer_xdr.cc.o
    ${POPCC_OUTPUT_DIR}/combox.cc.o
    ${POPCC_OUTPUT_DIR}/combox_factory.cc.o
    ${POPCC_OUTPUT_DIR}/combox_socket.cc.o
    ${POPCC_OUTPUT_DIR}/nodethread.cc.o
    ${POPCC_OUTPUT_DIR}/popc_logger.cpp.o
    ${POPCC_OUTPUT_DIR}/popc_search_node_info.cc.o
    ${POPCC_OUTPUT_DIR}/response.cc.o
    ${POPCC_OUTPUT_DIR}/request.cc.o
    ${POPCC_OUTPUT_DIR}/utils.cc.o
    ${POPCC_OUTPUT_DIR}/object.cc.o
    ${POPCC_OUTPUT_DIR}/system.cc.o
    ${POPCC_OUTPUT_DIR}/interface.cc.o
    ${POPCC_OUTPUT_DIR}/popc_allocator_tcpip_local.cpp.o
    ${POPCC_OUTPUT_DIR}/popc_allocator_tcpip_ssh.cpp.o
    ${POPCC_GENERATED_STUBS})

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
    OUTPUT libpopc_common.a
    COMMAND ar r libpopc_common.a ${intface_o_file} ${POPCC_GENERATED_FILES}
    DEPENDS ${intface_o_file} ${POPCC_GENERATED_FILES}
    COMMENT "Compile POP-C++ generated lib for popc_common")

add_custom_target(
    popc_common_link ALL
    DEPENDS libpopc_common.a ${intface_o_file} ${POPCC_GENERATED_FILES})

# Install all the files

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
