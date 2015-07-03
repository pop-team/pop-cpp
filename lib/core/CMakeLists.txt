#
# POP-C++
# Common (core) library build process
#   The core part of the library contains code that is common to both the dynamic and pseudodynamic parts of POP-C++
#
# AUTHOR: Laurent Winkler
# DATE: Jan 2015
#

set(POPCPP_DYNAMIC_INCLUDE_PATH "-I${CMAKE_SOURCE_DIR}/include/core")

set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

# Activate some warnings
add_definitions(-Wall -Wextra -Werror)

# Activate C++11
add_definitions(-std=c++11)

if(WIN32)
    set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc.exe)
    set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -no-async-allocation -cpp11 -cxxmain -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp.exe)
elseif(UNIX)
    set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)
    set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -no-async-allocation -cpp11 -cxxmain -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp)
endif(WIN32)

set(POPCPP_Parclass_COMPILER_FLAGS -parclass-nobroker -c -o)
set(POPCPP_ParclassForService_COMPILER_FLAGS -c -o)
set(POPCC_PARCLASS_COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS})
set(POPCC_PARCLASS_SERVICE_COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS})
set(POPCC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

# Build the interface (Win/Lin)
if(WIN32)
    set(intface_cc_file intface_windows.cc)
elseif(UNIX)
    set(intface_cc_file intface_linux.cc)
endif(WIN32)


set(POPCC_GENERATED_STUBS
#    ${POPCC_OUTPUT_DIR}/pop_service_base.ph.stub_client.o
)

set(POPCC_GENERATED_FILES
    # ${POPCC_OUTPUT_DIR}/utils.cc.o
    ${POPCC_GENERATED_STUBS}
)

add_library(popc_core
    accesspoint.cc
    allocobj.cc
    broker.cc
    broker_factory.cc
    broker_serve.cc
    buffer.cc
    buffer_factory.cc
    buffer_factory_finder.cc
    buffer_raw_factory.cc
    buffer_utils.cc
    buffer_xdr_factory.cc
    CMakeLists.txt
    combox.cc
    combox_uds.cc
    connection_uds.cc
    combox_socket.cc
    combox_factory.cc
    event.cc
    exception.cc
    memspool.cc
    mutex.cc
    od.cc
    logger.cpp
    popwayback.cc
    thread.cc
    timer.cc
    ${intface_cc_file}
    ${POPCC_GENERATED_FILES}
)

# Install all the files
set(POPCC_INCLUDE_INSTALL include/core)
set(POPCC_LIB_INSTALL lib/core)

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_core.a DESTINATION ${POPCC_LIB_INSTALL})
