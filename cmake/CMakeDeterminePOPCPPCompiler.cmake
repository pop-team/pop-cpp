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
# NOTE, a generator or a user may set CMAKE_POPCPP_COMPILER before
# loading this file to force a compiler 



IF(NOT CMAKE_POPCPP_COMPILER)

   # prefer the environement variable POPC_LOCATION
   IF($ENV{POPC_LOCATION} MATCHES ".+") 
      SET(POPCPP_BIN_PATH $ENV{POPC_LOCATION}/bin)
   ENDIF($ENV{POPC_LOCATION} MATCHES ".+")
   IF(NOT POPCPP_BIN_PATH)
      SET(POPCPP_BIN_PATH /usr/local/popc/bin)
   ENDIF(NOT POPCPP_BIN_PATH)

   
   # Set the compiler path with the bin path
   IF(CMAKE_POPCPP_COMPILER_INIT)
      SET(CMAKE_POPCPP_COMPILER ${CMAKE_POPCPP_COMPILER_INIT} CACHE PATH "POP-C++ Runtime")         
   ELSE(CMAKE_POPCPP_COMPILER_INIT)
      SET(CMAKE_POPCPP_COMPILER ${POPCPP_BIN_PATH}/popcc)
   ENDIF(CMAKE_POPCPP_COMPILER_INIT)

   

   # Set the runtime path
   IF(CMAKE_POPCPP_RUNTIME_INIT)
      SET(CMAKE_POPCPP_RUNTIME ${CMAKE_POPCPP_RUNTIME_INIT} CACHE PATH "POP-C++ Runtime")
   ELSE(CMAKE_POPCPP_RUNTIME_INIT)
      SET(CMAKE_POPCPP_RUNTIME ${POPCPP_BIN_PATH}/popcrun)
   ENDIF(CMAKE_POPCPP_RUNTIME_INIT)

   MESSAGE("Compiler is ${CMAKE_POPCPP_COMPILER}")    
   MESSAGE("Runtime is ${CMAKE_POPCPP_RUNTIME}")


ENDIF(NOT CMAKE_POPCPP_COMPILER)


MARK_AS_ADVANCED(CMAKE_POPCPP_COMPILER)  


# configure variables set in this file for fast reload later on
CONFIGURE_FILE(${CMAKE_ROOT}/Modules/CMakePOPCPPCompiler.cmake.in 
  ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakePOPCPPCompiler.cmake IMMEDIATE @ONLY)
SET(CMAKE_POPCPP_COMPILER_ENV_VAR "POPCPP_COMPILER")
