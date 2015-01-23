#
# POP-C++
# services components
#
# AUTHOR: vanhieu.nguyen
# DATE: 2013/07/25
#

if(WIN32)
    set(EXECUTABLE_EXTENSION .exe)
elseif(UNIX)
    set(EXECUTABLE_EXTENSION )
endif(WIN32)

set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc${EXECUTABLE_EXTENSION})
set(CMAKE_POPCPP_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcpp${EXECUTABLE_EXTENSION})
set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_POPCPP_COMPILER})

set(POPCPP_COMPILER_FLAGS -o)
set(POPCPP_Object_COMPILER_FLAGS -object -o)
set(POPCPP_ParclassForService_COMPILER_FLAGS -c -o)

set(POPCPP_SERVICES_INCLUDE_PATH "-I${CMAKE_SOURCE_DIR}/include/dynamic;-I${CMAKE_SOURCE_DIR}/include/core")
set(POPCPP_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/dynamic)
set(POPCPP_SERVICES_PATH ${CMAKE_SOURCE_DIR}/services/lib)

set(POPCPP_LIB_INSTALL lib/dynamic)
set(POPCPP_SERVICES_INSTALL services)

set(POPCC_COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS})
set(POPCC_COMMAND_OBJ ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Object_COMPILER_FLAGS})
set(POPCC_COMMAND_EXE ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_COMPILER_FLAGS})
set(POPCC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

# include_directories(${CMAKE_SOURCE_DIR}/ ${POPCPP_SERVICES_INCLUDE_PATH})
link_directories(${CMAKE_SOURCE_DIR}/lib/dynamic)

# Add more warnings
add_definitions(-Wall -Wextra -Werror)

# Function to compile a .ph file to a .ph.stub.o
function(popcc_compile_ph ph_file)
add_custom_command(
    OUTPUT ${POPCC_OUTPUT_DIR}/${ph_file}.stub.o
    COMMAND ${POPCC_COMMAND} ${POPCC_OUTPUT_DIR}/${ph_file}.stub.o ${CMAKE_CURRENT_SOURCE_DIR}/${ph_file} ${POPCPP_SERVICES_INCLUDE_PATH}
    WORKING_DIRECTORY ${POPCC_OUTPUT_DIR}
    DEPENDS ${ph_file}
)
endfunction(popcc_compile_ph)

# Function to compile a c++ file to a .o
function(popcc_compile_cxx cxx_file)
add_custom_command(
    OUTPUT ${POPCC_OUTPUT_DIR}/${cxx_file}.o
    COMMAND ${POPCC_COMMAND} ${POPCC_OUTPUT_DIR}/${cxx_file}.o ${CMAKE_CURRENT_SOURCE_DIR}/${cxx_file} ${POPCPP_SERVICES_INCLUDE_PATH}
    WORKING_DIRECTORY ${POPCC_OUTPUT_DIR}
    DEPENDS ${cxx_file}
)
endfunction(popcc_compile_cxx)

# Function to compile and link an executable from a .cc
function(popcc_compile_exec exec_file cxx_file)
popcc_compile_cxx(${cxx_file})
add_custom_target(
    ${exec_file} ALL
    COMMAND ${POPCC_COMMAND_EXE} ${POPCC_OUTPUT_DIR}/${exec_file} ${POPCC_OUTPUT_DIR}/${cxx_file}.o
        -L${POPCPP_LIB_PATH} -L${POPCPP_SERVICES_PATH} ${POPCC_OUTPUT_DIR}/libpopc_services.a
    WORKING_DIRECTORY ${POPCC_OUTPUT_DIR}
    DEPENDS ${POPCC_OUTPUT_DIR}/${cxx_file}.o ${POPCC_OUTPUT_DIR}/libpopc_services.a
)
endfunction(popcc_compile_exec)

# Function to compile and link an executable from a _obj.cc
function(popcc_compile_obj exec_file cxx_file)
popcc_compile_cxx(${cxx_file})
add_custom_target(
    ${exec_file} ALL
    COMMAND ${POPCC_COMMAND_OBJ} ${POPCC_OUTPUT_DIR}/${exec_file} ${POPCC_OUTPUT_DIR}/${cxx_file}.o
        -L${POPCPP_LIB_PATH} -L${POPCPP_SERVICES_PATH} ${POPCC_OUTPUT_DIR}/libpopc_services.a
    WORKING_DIRECTORY ${POPCC_OUTPUT_DIR}
    DEPENDS ${POPCC_OUTPUT_DIR}/${cxx_file}.o ${POPCC_OUTPUT_DIR}/libpopc_services.a
)
endfunction(popcc_compile_obj)

# Compile all .ph files

popcc_compile_ph(paroc_service_base.ph)
popcc_compile_ph(jobmgr.ph)
popcc_compile_ph(popc_search_node.ph)
popcc_compile_ph(codemgr.ph)
popcc_compile_ph(remotelog.ph)
popcc_compile_ph(objectmonitor.ph)
popcc_compile_ph(batchmgr.ph)
popcc_compile_ph(appservice.ph)
popcc_compile_ph(popfilemanager.ph)

set(POPCC_GENERATED_STUB
    ${POPCC_OUTPUT_DIR}/paroc_service_base.ph.stub.o
    ${POPCC_OUTPUT_DIR}/jobmgr.ph.stub.o
    ${POPCC_OUTPUT_DIR}/popc_search_node.ph.stub.o
    ${POPCC_OUTPUT_DIR}/codemgr.ph.stub.o
    ${POPCC_OUTPUT_DIR}/remotelog.ph.stub.o
    ${POPCC_OUTPUT_DIR}/objectmonitor.ph.stub.o
    ${POPCC_OUTPUT_DIR}/appservice.ph.stub.o
    ${POPCC_OUTPUT_DIR}/batchmgr.ph.stub.o
    ${POPCC_OUTPUT_DIR}/popfilemanager.ph.stub.o
)

add_custom_target(aaparoc_stub_services ALL DEPENDS ${POPCC_GENERATED_STUB})

# Compile all C++ files

popcc_compile_cxx(popc_logger.cpp)
popcc_compile_cxx(service_base.cc)
popcc_compile_cxx(jobmgr.cc)
popcc_compile_cxx(popc_search_node.cc)
popcc_compile_cxx(codemgr.cc)
popcc_compile_cxx(remotelog.cc)
popcc_compile_cxx(objectmonitor.cc)
popcc_compile_cxx(batchmgr.cc)
popcc_compile_cxx(appservice.cc)
popcc_compile_cxx(popfilemanager.cc)

set(POPCC_GENERATED_FILES
    ${POPCC_GENERATED_STUB}
    ${POPCC_OUTPUT_DIR}/service_base.cc.o
    ${POPCC_OUTPUT_DIR}/jobmgr.cc.o
    ${POPCC_OUTPUT_DIR}/popc_search_node.cc.o
    ${POPCC_OUTPUT_DIR}/codemgr.cc.o
    ${POPCC_OUTPUT_DIR}/remotelog.cc.o
    ${POPCC_OUTPUT_DIR}/objectmonitor.cc.o
    ${POPCC_OUTPUT_DIR}/appservice.cc.o
    ${POPCC_OUTPUT_DIR}/batchmgr.cc.o
    ${POPCC_OUTPUT_DIR}/popfilemanager.cc.o
    ${POPCC_OUTPUT_DIR}/popc_logger.cpp.o
)

# Generate the static library

add_custom_command(
    OUTPUT ${POPCC_OUTPUT_DIR}/libpopc_services.a
    COMMAND ar cru ${POPCC_OUTPUT_DIR}/libpopc_services.a ${POPCC_GENERATED_FILES}
    DEPENDS ${POPCC_GENERATED_FILES}
    COMMENT "Compile POP-C++ generated lib for popc_services")

#add_custom_target(abpopc_services ALL DEPENDS ${POPCC_GENERATED_FILES} ${POPCC_OUTPUT_DIR}/libpopc_services.a)

# Compile executables

popcc_compile_obj(popfilemanager popfilemanager_obj.cc)
popcc_compile_obj(popc_search_node popc_search_node_obj.cc)
popcc_compile_obj(jobmgr jobmgr_obj.cc)
popcc_compile_obj(appservice appservice_obj.cc)
popcc_compile_exec(localservice_launcher localservice_launcher.cc)
popcc_compile_exec(jobmgr_launcher jobmgr_launcher.cc)

# Install executables

install(PROGRAMS ${POPCC_OUTPUT_DIR}/popc_search_node${EXECUTABLE_EXTENSION} DESTINATION ${POPCPP_SERVICES_INSTALL})
install(PROGRAMS ${POPCC_OUTPUT_DIR}/jobmgr${EXECUTABLE_EXTENSION} DESTINATION ${POPCPP_SERVICES_INSTALL})
install(PROGRAMS ${POPCC_OUTPUT_DIR}/appservice${EXECUTABLE_EXTENSION} DESTINATION ${POPCPP_SERVICES_INSTALL})
install(PROGRAMS ${POPCC_OUTPUT_DIR}/localservice_launcher${EXECUTABLE_EXTENSION} DESTINATION ${POPCPP_SERVICES_INSTALL})
install(PROGRAMS ${POPCC_OUTPUT_DIR}/jobmgr_launcher${EXECUTABLE_EXTENSION} DESTINATION ${POPCPP_SERVICES_INSTALL})
install(PROGRAMS ${POPCC_OUTPUT_DIR}/popfilemanager${EXECUTABLE_EXTENSION} DESTINATION ${POPCPP_SERVICES_INSTALL})
install(PROGRAMS ${POPCC_OUTPUT_DIR}/libpopc_services.a DESTINATION ${POPCPP_LIB_INSTALL})
install(CODE "execute_process(COMMAND ${CMAKE_INSTALL_PREFIX}/sbin/popc_setup)")
