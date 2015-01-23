#
# POP-C++
# Common (dynamic) library build process
#
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

set(POPCC_INCLUDE_INSTALL include/dynamic)
set(POPCC_LIB_INSTALL lib/dynamic)

set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

# Activate some warnings
add_definitions(-Wall -Wextra -Werror)

if(WIN32)
    set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc.exe)
    set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -cxxmain -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp.exe)
elseif(UNIX)
    set(CMAKE_POPCC_COMPILER ${CMAKE_SOURCE_DIR}/parser/popcc)
    set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -cxxmain -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_SOURCE_DIR}/parser/popcpp)
endif(WIN32)

# set(POPCPP_Parclass_COMPILER_FLAGS -parclass-nobroker -c -o)
# set(POPCPP_ParclassForService_COMPILER_FLAGS -c -o)
# set(POPCC_PARCLASS_COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_Parclass_COMPILER_FLAGS})
# set(POPCC_PARCLASS_SERVICE_COMMAND ${CMAKE_POPCC_COMPILER} ${POPCPP_FLAGS} ${POPCPP_ParclassForService_COMPILER_FLAGS})
# set(POPCC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY})

# Build the interface (Win/Lin)
if(WIN32)
    set(intface_cc_file popc_intface_windows.cc)
elseif(UNIX)
    set(intface_cc_file popc_intface_linux.cc)
endif(WIN32)

add_library(popc_core_part
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
combox_socket.cc
debug.cc
event.cc
exception.cc
memspool.cc
mutex.cc
od.cc
popc_logger.cpp
popwayback.cc
string.cc
thread.cc
timer.cc
utils.cc
${intface_cc_file}
)
# TODO:
# see what to do with benchmark.cc
