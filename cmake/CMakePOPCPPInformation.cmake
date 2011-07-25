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
   SET(CMAKE_POPCPP_OBJECT_FLAGS -object -o)
ENDIF(NOT CMAKE_POPCPP_OBJECT_FLAGS)

IF(NOT CMAKE_POPCPP_MAIN_FLAGS)
   SET(CMAKE_POPCPP_MAIN_FLAGS -o)
ENDIF(NOT CMAKE_POPCPP_MAIN_FLAGS)


# Macro used to parse arguments from another macro
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

# Get the first element of the list
MACRO(CAR var)
  SET(${var} ${ARGV1})
ENDMACRO(CAR)

# Get the list without the first element
MACRO(CDR var junk)
  SET(${var} ${ARGN})
ENDMACRO(CDR)


# POP-C++ special macro
# This macro is used to compile a parallel object
MACRO(ADD_POPC_OBJECT)
#   MESSAGE("CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
#   MESSAGE("CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
#   MESSAGE("CMAKE_FILES_DIRECTORY ${CMAKE_FILES_DIRECTORY}")

   # Be sure that the SOURCE varibale is empty
   SET(SOURCES)
   SET(TARGET_NAME)
   SET(OBJECT_DIR)
   # Parse the arguments for this macro
   PARSE_ARGUMENTS(PAROBJ
      "FLAGS"
      ""
      ${ARGN}
   )

   # Get the first arg
   CAR(OBJECT_NAME ${PAROBJ_DEFAULT_ARGS})

   # Get all the args without the first
   CDR(OBJECT_SOURCES ${PAROBJ_DEFAULT_ARGS})
  

   SET(OBJECT_DIR ".${CMAKE_FILES_DIRECTORY}/${OBJECT_NAME}.dir")
   EXEC_PROGRAM(mkdir
                ARGS "-p ${OBJECT_DIR}")

   # If no flags set the default one
   IF(NOT PAROBJ_FLAGS)
      set(FLAGS_POPCPP ${CMAKE_POPCPP_OBJECT_FLAGS})
   ENDIF(NOT PAROBJ_FLAGS)

   # Create white-spaced list for the flags
   FOREACH(flag ${PAROBJ_FLAGS})
      set(FLAGS_POPCPP ${FLAGS_POPCPP} ${flag})
   ENDFOREACH(flag ${PAROBJ_FLAGS})

   # Copy source files in CMakeFiles dir
   

   # Create white-spaced list for the source files
   FOREACH(source ${OBJECT_SOURCES})
      set(SOURCES ${SOURCES} ../../${source})
   ENDFOREACH(source ${OBJECT_SOURCES})

   


  # MESSAGE("POPCPP: Object name: ${OBJECT_NAME}")
  # MESSAGE("POPCPP: Sources: ${SOURCES}")
  # MESSAGE("POPCPP: Flags: ${FLAGS_POPCPP}")


   #MESSAGE("${CMAKE_POPCPP_COMPILER} ${FLAGS_POPCPP} ${OBJECT_NAME} ${SOURCES}")
   #MESSAGE("Current directory ${CMAKE_CURRENT_SOURCE_DIR}")

#   EXEC_PROGRAM(${CMAKE_POPCPP_COMPILER} 
#                ARGS "${FLAGS_POPCPP} ${OBJECT_NAME} ${SOURCES}"
 #  )

   SET(TARGET_NAME "${OBJECT_NAME}")
   SET(COMPILE_COMMAND ${CMAKE_POPCPP_COMPILER} ${FLAGS_POPCPP} ${OBJECT_NAME} ${SOURCES})
   MESSAGE("${COMPILE_COMMAND}")
   ADD_CUSTOM_TARGET(${TARGET_NAME} ALL 
                     COMMAND ${COMPILE_COMMAND}
                     COMMAND cp ${OBJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME}
                     WORKING_DIRECTORY ${OBJECT_DIR}
                     VERBATIM
                    )

   
   SET_DIRECTORY_PROPERTIES(PROPERTIES
                            ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME})
               

#   ADD_DEPENDENCIES(build ${OBJECT_NAME})


   SET(PAROBJ_FLAGS)    
   SET(FLAGS_POPCPP)
ENDMACRO(ADD_POPC_OBJECT)


#####################################################################################
#
#   POP-C++ Main compilation
#
#####################################################################################
MACRO(ADD_POPC_MAIN)
   # Clear var before using them
   SET(LIST_MAIN_SOURCES) 
   SET(TARGET_NAME)
   SET(OBJECT_DIR)

   PARSE_ARGUMENTS(POPCPPMAIN
      "FLAGS"
      ""
      ${ARGN}
   )
   CAR(MAIN_NAME ${POPCPPMAIN_DEFAULT_ARGS})
   CDR(MAIN_SOURCES ${POPCPPMAIN_DEFAULT_ARGS})

   SET(OBJECT_DIR .${CMAKE_FILES_DIRECTORY}/${MAIN_NAME}.dir)
   EXEC_PROGRAM(mkdir
                ARGS "-p ${OBJECT_DIR}")

   IF(NOT POPCPPMAIN_FLAGS)
      set(FLAGS_MAIN ${CMAKE_POPCPP_MAIN_FLAGS})
   ENDIF(NOT POPCPPMAIN_FLAGS)

   FOREACH(flag ${POPCPPMAIN_FLAGS})
      set(FLAGS_MAIN ${FLAGS_MAIN} ${flag})
   ENDFOREACH(flag ${POPCPPMAIN_FLAGS})

   FOREACH(source ${MAIN_SOURCES})
   #   EXEC_PROGRAM(cp 
    #              ARGS "${source} ${OBJECT_DIR}/${source}")
      set(LIST_MAIN_SOURCES ${LIST_MAIN_SOURCES} ../../${source})
   ENDFOREACH(source ${MAIN_SOURCES})

   SET(TARGET_NAME ${MAIN_NAME})
   SET(COMPILE_COMMAND ${CMAKE_POPCPP_COMPILER} ${FLAGS_MAIN} ${MAIN_NAME} ${LIST_MAIN_SOURCES})

   ADD_CUSTOM_TARGET(${TARGET_NAME} ALL 
                     COMMAND ${COMPILE_COMMAND}
                     COMMAND cp ${MAIN_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_NAME}
                     WORKING_DIRECTORY ${OBJECT_DIR}
                     VERBATIM
                    )

   set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${MAIN_NAME})
   
   
ENDMACRO(ADD_POPC_MAIN)

#####################################################################################
#
#   Object map creation macro
#
#####################################################################################
MACRO(ADD_POPC_OBJMAP)
   SET(TARGET_NAME)
   SET(OBJMAP_COMMAND)  
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
      SET(TARGET_NAME ${PAROBJ}.map)
      SET(OBJMAP_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${par} -listlong >> ${POPCPPOBJMAP_OBJECTMAP})
      ADD_CUSTOM_TARGET(${TARGET_NAME} ALL
                        COMMAND ${OBJMAP_COMMAND}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        VERBATIM)
   ENDFOREACH(par ${PAROBJ})
   

ENDMACRO(ADD_POPC_OBJMAP)


MACRO(ADD_POPC_RUN)
   MESSAGE("popcrun ${ARGV0} ${ARGV1}")
   SET(RUN_COMMAND popcrun ${ARGV0} ./${ARGV1})
   ADD_CUSTOM_TARGET(run
                     COMMAND ${RUN_COMMAND}
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
ENDMACRO(ADD_POPC_RUN)
