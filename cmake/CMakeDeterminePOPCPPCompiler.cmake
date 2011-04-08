#=============================================================================
# GRID & Cloud Computing Group (EIA-FR, Switzerland)
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

# determine the compiler to use for POP-C++ programs


SET(CMAKE_POPCPP_COMPILER /home/visag/popc/bin/popcc)
SET(POPCPP_USER_BIN_PATH $ENV{POPC_LOCATION}/bin)
SET(POPCPP_DEFAULT_BIN_PATH /usr/local/popc)
FIND_PROGRAM(CMAKE_POPCPP_COMPILER popcc PATHS ${POPCPP_DEFAULT_BIN_PATHS} ${POPCPP_USER_BIN_PATH})
MESSAGE(STATUS ${CMAKE_POPCPP_COMPILER})

MARK_AS_ADVANCED(CMAKE_POPCPP_COMPILER)  


# configure variables set in this file for fast reload later on
CONFIGURE_FILE(${CMAKE_ROOT}/Modules/CMakePOPCPPCompiler.cmake.in 
  ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakePOPCPPCompiler.cmake IMMEDIATE @ONLY)
SET(CMAKE_POPCPP_COMPILER_ENV_VAR "POPCC")
