cmake_minimum_required(VERSION 2.6)

project(POPC_PARSER)

include(CheckIncludeFile)
include(CheckLibraryExists)

if(NOT EXISTS "../config.h")
  message(SEND_ERROR "You must configure POP-C++ main project first!")
endif(NOT EXISTS "../config.h")

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

include_directories(${CMAKE_SOURCE_DIR}/../ ${CMAKE_SOURCE_DIR}/../include)             

add_custom_target(gen 
                  COMMAND ${BISON} -y -b parser -d parser.y
                  COMMAND mv parser.tab.c parser.tab.cc
                  COMMAND ${FLEX} -oparser.yy.cc parser.lex
                  DEPENDS parser.y                  
                  COMMENT "Generating parser files")                     

#add_custom_target(gen DEPENDS parser.tmp)

add_custom_command(OUTPUT parser.tab.h
                  COMMENT "Generate parser.tab.h")

add_custom_command(OUTPUT parser.tab.cc
                  COMMENT "Generate parser.tab.cc")

add_custom_command(OUTPUT parser.yy.cc
                  COMMENT "Generate parser.yy.cc")
                   


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
  ${CMAKE_SOURCE_DIR}/../lib/utils.cc
  ${CMAKE_SOURCE_DIR}/../lib/debug.cc
  )
add_dependencies(popcpp gen)  
  
  
# Build the popcc executable 
add_executable(popcc
               popcc.cc 
               ${CMAKE_SOURCE_DIR}/../lib/utils.cc
               )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcc.cc.in ${CMAKE_CURRENT_SOURCE_DIR}/popcc.cc)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "parser.tab.h;parser.tab.cc;parser.yy.cc;")

IF (UNIX)
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
   *~
  )
  
  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -Rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean
  )
ENDIF(UNIX)

