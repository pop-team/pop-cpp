CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(install-cmake NONE)
MESSAGE("-- [POP-C++ CMake Support] Installing POP-C++ CMake support in ${CMAKE_ROOT}")
MESSAGE("-- [POP-C++ CMake Support] Be sure to have the right in the destination directory or use sudo")
EXECUTE_PROCESS(COMMAND cp CMakeDeterminePOPCPPCompiler.cmake ${CMAKE_ROOT}/Modules/ 
               OUTPUT_QUIET)
EXECUTE_PROCESS(COMMAND cp CMakePOPCPPCompiler.cmake.in ${CMAKE_ROOT}/Modules/ 
               OUTPUT_QUIET)
EXECUTE_PROCESS(COMMAND cp CMakePOPCPPInformation.cmake ${CMAKE_ROOT}/Modules/ 
               OUTPUT_QUIET)
MESSAGE("-- [POP-C++ CMake Support] Installation done")
