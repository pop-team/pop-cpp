cmake_minimum_required(VERSION 2.6)

project(POPC_PARSER)

include(CheckIncludeFile)
include(CheckLibraryExists)

# Add more warnings
add_definitions(-Wall -Wextra -Werror)

if(NOT POPCPP_COMPILER)
    message(STATUS "Configuring POP-C++ Compiler separately than library project.")
    if(NOT EXISTS "../config.h")
        message(SEND_ERROR "You must configure POP-C++ main project first!")
    endif(NOT EXISTS "../config.h")
endif(NOT POPCPP_COMPILER)

# Define user specific option. Disable by default.
option(MPI_SUPPORT "MPI Support" OFF)
option(XMP_SUPPORT "XMP Support" OFF)

# Locate the flex executable
find_program(FLEX flex DOC "Path to the flex lexical analyser generator.")
if(NOT DEFINED FLEX)
    message(SEND_ERROR "Flex not found.")
endif(NOT DEFINED FLEX)
message(STATUS "Flex found at ${FLEX}")

# Locate the Bison executable
find_program(BISON bison DOC "Path to the bison parser generator.")
if(NOT DEFINED BISON)
    message(SEND_ERROR "Bison not found.")
endif(NOT DEFINED BISON)
message(STATUS "Bison found at ${BISON}")

if(POPCPP_COMPILER)
    include_directories(${CMAKE_SOURCE_DIR}/parser/ ${CMAKE_SOURCE_DIR}/include/dynamic ${CMAKE_SOURCE_DIR}/)
else(POPCPP_COMPILER)
    include_directories(${CMAKE_SOURCE_DIR}/../ ${CMAKE_SOURCE_DIR}/../include/dynamic)
endif(POPCPP_COMPILER)

add_custom_target(gen
    COMMAND ${BISON} -y -b parser -d parser.y
    COMMAND mv parser.tab.c parser.tab.cc
    COMMAND ${FLEX} -oparser.yy.cc parser.lex
    DEPENDS parser.y
    COMMENT "Generating parser files")

add_custom_command(
    OUTPUT parser.tab.h
    COMMENT "Generate parser.tab.h")

add_custom_command(
    OUTPUT parser.tab.cc
    COMMENT "Generate parser.tab.cc")

add_custom_command(
    OUTPUT parser.yy.cc
    COMMENT "Generate parser.yy.cc")

if(POPCPP_COMPILER)
    set(POPCPP_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/dynamic)
else(POPCPP_COMPILER)
    set(POPCPP_LIB_PATH ${CMAKE_SOURCE_DIR}/../lib/dynamic)
endif(POPCPP_COMPILER)

if(UNIX)
    set(intface_file ${POPCPP_LIB_PATH}/popc_intface_linux.cc)
elseif(WIN32)
    set(intface_file ${POPCPP_LIB_PATH}/popc_intface_windows.cc)
endif(UNIX)

add_executable(popcpp
    parser.cc
    parser_common.cc
    parser_common.h
    codefile.cc
    othercode.cc
    classmember.cc
    class.cc
    packobject.cc
    parser.tab.cc
    parser.yy.cc
    parser.h
    parser.tab.h
    parser_common.h
    type.h
    typearray.cc
    type.cc
    typeequal.cc
    typeptr.cc
    typestruct.cc
    typeseqclass.cc
    typeclassstruct.cc
    typetemplate.cc
    ${POPCPP_LIB_PATH}/utils.cc
    ${POPCPP_LIB_PATH}/debug.cc
    ${intface_file})

# Make sure the lexer/parser are generated
add_dependencies(popcpp gen)

# Build the popcc executable
add_executable(popcc
    popcc.cc
    ${POPCPP_LIB_PATH}/utils.cc
    ${intface_file})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcc.cc.in ${CMAKE_CURRENT_SOURCE_DIR}/popcc.cc)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "parser.tab.h;parser.tab.cc;parser.yy.cc;")

# Install programs in the bin folder
if(UNIX)
    install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcc DESTINATION bin)
    install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcpp DESTINATION bin)
elseif(WIN32)
    install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcc.exe DESTINATION bin)
    install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcpp.exe DESTINATION bin)
endif(UNIX)

if(NOT POPCPP_COMPILER)
    ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
    SET(DISTCLEANED
        cmake.depends
        cmake.check_depends
        CMakeCache.txt
        CMakeFiles
        cmake.check_cache
        *.cmake
        Makefile
        core core.*
        gmon.out
        popcc.cc
        *~)

    ADD_CUSTOM_COMMAND(
        DEPENDS clean
        COMMENT "distribution clean"
        COMMAND rm
        ARGS    -Rf CMakeTmp ${DISTCLEANED}
        TARGET  distclean)
endif(NOT POPCPP_COMPILER)
