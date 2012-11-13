include_directories(${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/include)




add_custom_command(OUTPUT parser.tab.h
                   COMMAND bison -b parser -d parser.y
                   COMMAND mv parser.tab.c parser.tab.cc
                   COMMAND flex -o parser.yy.cc parser.lex
                   DEPENDS parser.y parser.lex
                   COMMENT "Running Bison")
                   
add_custom_target(parser-yacc ALL DEPENDS parser.tab.h) 

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
  ${CMAKE_SOURCE_DIR}/lib/utils.cc
  ${CMAKE_SOURCE_DIR}/lib/debug.cc
  )
  
add_executable(popcc
  popcc.cc 
  ${CMAKE_SOURCE_DIR}/lib/utils.cc
  )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcc.cc.in ${CMAKE_CURRENT_SOURCE_DIR}/popcc.cc)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "parser.tab.h;parser.tab.cc;parser.yy.cc;")
