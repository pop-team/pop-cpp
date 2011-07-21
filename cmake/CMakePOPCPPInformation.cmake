IF(CMAKE_USER_MAKE_RULES_OVERRIDE)
   INCLUDE(${CMAKE_USER_MAKE_RULE_OVERRIDE})
ENDIF(CMAKE_USER_MAKE_RULES_OVERRIDE)

IF(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX)
   INCLUDE(${CMAKE_USER_MAKE_RULE_OVERRIDE_CXX})
ENDIF(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX)


# Define how cmake must compile a POP-C++ object
IF(NOT CMAKE_POPCPP_COMPILE_OBJECT)
   SET(CMAKE_POPCPP_COMPILE_OBJECT "")
   SET(CMAKE_POPCPP_COMPILE_MAIN "")
   SET(CMAKE_POPCPP_LINK_EXECUTABLE "")
ENDIF(NOT CMAKE_POPCPP_COMPILE_OBJECT)




IF(NOT CMAKE_POPCPP_OBJECT_FLAGS)
   SET(CMAKE_POPCPP_OBJECT_FLAGS "-object -o")
ENDIF(NOT CMAKE_POPCPP_OBJECT_FLAGS)

IF(NOT CMAKE_POPCPP_MAIN_FLAGS)
   SET(CMAKE_POPCPP_MAIN_FLAGS "-o")
ENDIF(NOT CMAKE_POPCPP_MAIN_FLAGS)

MACRO(PARSE_ARGUMENTS prefix arg_names option_names)
  SET(DEFAULT_ARGS)
  FOREACH(arg_name ${arg_names})    
    SET(${prefix}_${arg_name})
  ENDFOREACH(arg_name)
  FOREACH(option ${option_names})
    SET(${prefix}_${option} FALSE)
  ENDFOREACH(option)

  SET(current_arg_name DEFAULT_ARGS)
  SET(current_arg_list)
  FOREACH(arg ${ARGN})            
    SET(larg_names ${arg_names})    
    LIST(FIND larg_names "${arg}" is_arg_name)                   
    IF (is_arg_name GREATER -1)
      SET(${prefix}_${current_arg_name} ${current_arg_list})
      SET(current_arg_name ${arg})
      SET(current_arg_list)
    ELSE (is_arg_name GREATER -1)
      SET(loption_names ${option_names})    
      LIST(FIND loption_names "${arg}" is_option)            
      IF (is_option GREATER -1)
	     SET(${prefix}_${arg} TRUE)
      ELSE (is_option GREATER -1)
	     SET(current_arg_list ${current_arg_list} ${arg})
      ENDIF (is_option GREATER -1)
    ENDIF (is_arg_name GREATER -1)
  ENDFOREACH(arg)
  SET(${prefix}_${current_arg_name} ${current_arg_list})
ENDMACRO(PARSE_ARGUMENTS)

MACRO(CAR var)
  SET(${var} ${ARGV1})
ENDMACRO(CAR)

MACRO(CDR var junk)
  SET(${var} ${ARGN})
ENDMACRO(CDR)


MACRO(ADD_PARALLEL_OBJECT)
   SET(SOURCES)
   PARSE_ARGUMENTS(PAROBJ
      "FLAGS"
      ""
      ${ARGN}
   )
   CAR(OBJECT_NAME ${PAROBJ_DEFAULT_ARGS})
   CDR(OBJECT_SOURCES ${PAROBJ_DEFAULT_ARGS})
  

   IF(NOT PAROBJ_FLAGS)
      set(FLAGS_POPCPP ${CMAKE_POPCPP_OBJECT_FLAGS})
   ENDIF(NOT PAROBJ_FLAGS)

   FOREACH(flag ${PAROBJ_FLAGS})
      MESSAGE("Assign flags")
      set(FLAGS_POPCPP "${FLAGS_POPCPP} ${flag}")
   ENDFOREACH(flag ${PAROBJ_FLAGS})

   FOREACH(source ${OBJECT_SOURCES})
      set(SOURCES "${SOURCES} ${source}")
   ENDFOREACH(source ${OBJECT_SOURCES})


   MESSAGE("POPCPP: Object name: ${OBJECT_NAME}")
   MESSAGE("POPCPP: Sources: ${SOURCES}")
   MESSAGE("POPCPP: Flags: ${FLAGS_POPCPP}")


   MESSAGE("${CMAKE_POPCPP_COMPILER} ${FLAGS_POPCPP} ${OBJECT_NAME} ${SOURCES}")
   MESSAGE("Current directory ${CMAKE_CURRENT_SOURCE_DIR}")

   EXEC_PROGRAM(${CMAKE_POPCPP_COMPILER} 
                ARGS "${FLAGS_POPCPP} ${OBJECT_NAME} ${SOURCES}"
   )

            
ENDMACRO(ADD_PARALLEL_OBJECT)


#####################################################################################
#
#   POP-C++ Main compilation
#
#####################################################################################
MACRO(ADD_POPCPP_MAIN)
   SET(SOURCES)
   PARSE_ARGUMENTS(POPCPPMAIN
      "FLAGS"
      ""
      ${ARGN}
   )
   CAR(MAIN_NAME ${POPCPPMAIN_DEFAULT_ARGS})
   CDR(MAIN_SOURCES ${POPCPPMAIN_DEFAULT_ARGS})

   IF(NOT POPCPPMAIN_FLAGS)
      set(FLAGS_MAIN ${CMAKE_POPCPP_MAIN_FLAGS})
   ENDIF(NOT POPCPPMAIN_FLAGS)

   FOREACH(flag ${POPCPPMAIN_FLAGS})
      set(FLAGS_MAIN "${FLAGS_MAIN} ${flag}")
   ENDFOREACH(flag ${POPCPPMAIN_FLAGS})

   FOREACH(source ${MAIN_SOURCES})
      set(LIST_MAIN_SOURCES "${LIST_MAIN_SOURCES} ${source}")
   ENDFOREACH(source ${MAIN_SOURCES})

   MESSAGE("SOURCES ${LIST_MAIN_SOURCES}")

   EXEC_PROGRAM(${CMAKE_POPCPP_COMPILER} 
      ARGS "${FLAGS_MAIN} ${MAIN_NAME} ${LIST_MAIN_SOURCES}"
   )
   
   
ENDMACRO(ADD_POPCPP_MAIN)

#####################################################################################
#
#   Object map creation macro
#
#####################################################################################
MACRO(OBJECT_MAP)
   # Parse arguments in the command line
   PARSE_ARGUMENTS(POPCPPOBJMAP
      "OBJECTMAP"
      "NOT_APPEND"
      ${ARGN}
   )

   # Get list of object to add to the object map
   SET(PAROBJ ${POPCPPOBJMAP_DEFAULT_ARGS})
   
   # If no object map filename is specified, set a default one
   IF(NOT POPCPPOBJMAP_OBJECTMAP)
      set(POPCPPOBJMAP_OBJECTMAP "obj.map")
   ENDIF(NOT POPCPPOBJMAP_OBJECTMAP)

   IF(POPCPPOBJMAP_NOT_APPEND)
      EXEC_PROGRAM(rm
         ARGS "-f ${CMAKE_CURRENT_SOURCE_DIR}/${POPCPPOBJMAP_OBJECTMAP}")
   ENDIF(POPCPPOBJMAP_NOT_APPEND)

   # Execute each object to add there mapping in the file
   FOREACH(par ${PAROBJ})
      MESSAGE("${CMAKE_CURRENT_SOURCE_DIR}/${par} -listlong >> ${POPCPPOBJMAP_NAME}")
      EXEC_PROGRAM(${CMAKE_CURRENT_SOURCE_DIR}/${par}
         ARGS "-listlong >> ${POPCPPOBJMAP_OBJECTMAP}")
   ENDFOREACH(par ${PAROBJ})
   

ENDMACRO(OBJECT_MAP)
