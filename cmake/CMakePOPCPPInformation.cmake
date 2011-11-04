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
   # Be sure that the SOURCE varibale is empty
   SET(SOURCES)
   SET(TARGET_NAME)
   SET(OBJECT_DIR)
   SET(DEPEN_POPCPP)
   SET(PAROBJ_DEP)
   # Parse the arguments for this macro
   PARSE_ARGUMENTS(PAROBJ
      "FLAGS;DEP"
      "NOBROKER;NOPARALLEL"
      ${ARGN}
   )
   
   # Create the working directory for compilation if not yet created
   SET(OBJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/pop.dir")
   EXEC_PROGRAM(mkdir ARGS "-p ${OBJECT_DIR}")

   # Compilation of a parallel object in standard mode
   IF(${PAROBJ_NOBROKER} STREQUAL "FALSE")
      # If no flags set the default one
      IF(NOT PAROBJ_FLAGS)
         set(FLAGS_POPCPP ${CMAKE_POPCPP_OBJECT_FLAGS})
      ENDIF(NOT PAROBJ_FLAGS)
      
      IF(${PAROBJ_NOPARALLEL} STREQUAL "FALSE")
         # Get the first arg as name of the compiled file
         CAR(OBJECT_NAME ${PAROBJ_DEFAULT_ARGS})
         # Get all the args without the first as sources for compilation
         CDR(OBJECT_SOURCES ${PAROBJ_DEFAULT_ARGS})
         SET(STUB_NAME)
         SET(O_NAME)
         STRING(REGEX REPLACE "\\..*" ".stub.o" STUB_NAME ${OBJECT_NAME})
         STRING(REGEX REPLACE "\\..*" ".o" O_NAME ${OBJECT_NAME})
      ELSE()
         CAR(FIRST_SOURCE ${PAROBJ_DEFAULT_ARGS})
         SET(OBJECT_SOURCES ${PAROBJ_DEFAULT_ARGS})
         SET(STUB_NAME)
         SET(O_NAME)
         STRING(REGEX REPLACE "\\..*" ".stub.o" STUB_NAME ${FIRST_SOURCE})
         STRING(REGEX REPLACE "\\..*" ".o" O_NAME ${FIRST_SOURCE})
      ENDIF()     

      # Create white-spaced list for the flags
      FOREACH(flag ${PAROBJ_FLAGS})
         set(FLAGS_POPCPP ${FLAGS_POPCPP} ${flag})
      ENDFOREACH(flag ${PAROBJ_FLAGS})

      # Create white-spaced list for the source files
      FOREACH(source ${OBJECT_SOURCES})
         set(SOURCES ${SOURCES} ../../${source})
      ENDFOREACH(source ${OBJECT_SOURCES})


      # Set the variable for compilation
      IF(${PAROBJ_NOPARALLEL} STREQUAL "FALSE")
         SET(TARGET_NAME "${OBJECT_NAME}")
         SET(COMPILE_COMMAND ${CMAKE_POPCPP_COMPILER} ${FLAGS_POPCPP} ${OBJECT_NAME} ${SOURCES})

         # Create the custom target with the POP-C++ compilation
         ADD_CUSTOM_TARGET(${TARGET_NAME} ALL 
                        COMMAND ${COMPILE_COMMAND}
                        COMMAND cp ${OBJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME}
                        WORKING_DIRECTORY ${OBJECT_DIR}
                        VERBATIM
                       )
      ELSE()
         
         SET(TARGET_NAME "object-${FIRST_SOURCE}")
         SET(COMPILE_COMMAND ${CMAKE_POPCPP_COMPILER} ${FLAGS_POPCPP} ${SOURCES})
         # Create the custom target with the POP-C++ compilation
         ADD_CUSTOM_TARGET(${TARGET_NAME} ALL 
                        COMMAND ${COMPILE_COMMAND}
                        WORKING_DIRECTORY ${OBJECT_DIR}
                        VERBATIM
                       )
      ENDIF()

      # Add dependencies to the target if there are some specified
      IF(PAROBJ_DEP)
         
         FOREACH(dep ${PAROBJ_DEP})
           set(DEPEN_POPCPP ${DEPEN_POPCPP} ${dep})
         ENDFOREACH(dep ${PAROBJ_DEP})
         ADD_DEPENDENCIES(${TARGET_NAME} ${DEPEN_POPCPP})
      ENDIF(PAROBJ_DEP)
      # Set files to be deleted by clean target
      GET_DIRECTORY_PROPERTY(DIRPROP ADDITIONAL_MAKE_CLEAN_FILES)
      SET(DIRDROP ${DIRDROP} ${CMAKE_CURRENT_SOURCE_DIR}/${OBJECT_NAME} ${STUB_NAME} ${O_NAME})
      SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${DIRDROP}")

                  
   # Compilation of a parallel object without broker
   ELSE(${PAROBJ_NOBROKER} STREQUAL "FALSE")
      # Get all paramaters as sources for the compilation
      SET(OBJECT_SOURCES ${PAROBJ_DEFAULT_ARGS})
      # Set the target name for the special compilation
      CAR(FIRST_FILE ${PAROBJ_DEFAULT_ARGS})
      SET(TARGET_NAME "nobroker-${FIRST_FILE}")

      # If no flags set the default one
      IF(NOT PAROBJ_FLAGS)
         set(FLAGS_POPCPP -parclass-nobroker -c)
      ELSE(NOT PAROBJ_FLAGS)
         # Create white-spaced list for the flags
         FOREACH(flag ${PAROBJ_FLAGS})
            set(FLAGS_POPCPP ${FLAGS_POPCPP} ${flag})
         ENDFOREACH(flag ${PAROBJ_FLAGS})
      ENDIF(NOT PAROBJ_FLAGS)

      # Create white-spaced list for the source files
      FOREACH(source ${OBJECT_SOURCES})
         set(SOURCES ${SOURCES} ../../${source})
      ENDFOREACH(source ${OBJECT_SOURCES})
      # Set the compilation command
      SET(COMPILE_COMMAND ${CMAKE_POPCPP_COMPILER} ${FLAGS_POPCPP} ${SOURCES})

      # Create the custom target with the POP-C++ compilation
      ADD_CUSTOM_TARGET(${TARGET_NAME} ALL 
                        COMMAND echo ${COMPILE_COMMAND}
                        COMMAND ${COMPILE_COMMAND}
                        WORKING_DIRECTORY ${OBJECT_DIR}
                        VERBATIM
                       )
      # Add dependencies to the target if there are some specified
      IF(PAROBJ_DEP)
         SET(DEPEN_POPCPP)
         FOREACH(dep ${PAROBJ_DEP})
           set(DEPEN_POPCPP ${DEPEN_POPCPP} ${dep})
         ENDFOREACH(dep ${PAROBJ_DEP})
         ADD_DEPENDENCIES(${TARGET_NAME} ${DEPEN_POPCPP})
      ENDIF(PAROBJ_DEP)
      SET(PAROBJ_NOBROKER)
   ENDIF(${PAROBJ_NOBROKER} STREQUAL "FALSE")

   SET(PAROBJ_FLAGS)    
   SET(PAROBJ_DEP)
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
   SET(DEPEN_POPCPP)

   PARSE_ARGUMENTS(POPCPPMAIN
      "FLAGS;DEP"
      ""
      ${ARGN}
   )
   
   CAR(MAIN_NAME ${POPCPPMAIN_DEFAULT_ARGS})
   CDR(MAIN_SOURCES ${POPCPPMAIN_DEFAULT_ARGS})

   SET(OBJECT_DIR .${CMAKE_FILES_DIRECTORY}/pop.dir)
   EXEC_PROGRAM(mkdir ARGS "-p ${OBJECT_DIR}")

   IF(NOT POPCPPMAIN_FLAGS)
      set(FLAGS_MAIN ${CMAKE_POPCPP_MAIN_FLAGS})
   ENDIF(NOT POPCPPMAIN_FLAGS)

   FOREACH(flag ${POPCPPMAIN_FLAGS})
      set(FLAGS_MAIN ${FLAGS_MAIN} ${flag})
   ENDFOREACH(flag ${POPCPPMAIN_FLAGS})

   SET(ADDITIONAL_REMOVE)
   FOREACH(source ${MAIN_SOURCES})
      IF("${source}" MATCHES "\\.ph$")
         SET(STUB_NAME)
         STRING(REGEX REPLACE "\\..*" ".stub.o" STUB_NAME ${source})
         SET(ADDITIONAL_REMOVE ${ADDITIONAL_REMOVE} ${STUB_NAME})
      ENDIF()
      IF("${source}" MATCHES "\\.cc$")
         SET(O_NAME) 
         STRING(REGEX REPLACE "\\..*" ".o" O_NAME ${source})
         SET(ADDITIONAL_REMOVE ${ADDITIONAL_REMOVE} ${O_NAME})
      ENDIF()
      set(LIST_MAIN_SOURCES ${LIST_MAIN_SOURCES} ../../${source})
   ENDFOREACH(source ${MAIN_SOURCES})

   SET(TARGET_NAME ${MAIN_NAME})
   SET(COMPILE_COMMAND ${CMAKE_POPCPP_COMPILER} ${FLAGS_MAIN} ${MAIN_NAME} ${LIST_MAIN_SOURCES})

   GET_TARGET_PROPERTY(TAR_LOC ${TARGET_NAME} LOCATION)



   ADD_CUSTOM_TARGET(${TARGET_NAME} ALL 
                     COMMAND echo ${COMPILE_COMMAND}
                     COMMAND ${COMPILE_COMMAND}
                     COMMAND cp ${MAIN_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_NAME}
                     WORKING_DIRECTORY ${OBJECT_DIR}
                     VERBATIM
                    )
   IF(POPCPPMAIN_DEP)
      FOREACH(dep ${POPCPPMAIN_DEP})
         set(DEPEN_POPCPP ${DEPEN_POPCPP} ${dep})
      ENDFOREACH(dep ${POPCPPMAIN_DEP})
      ADD_DEPENDENCIES(${TARGET_NAME} ${DEPEN_POPCPP})
   ENDIF(POPCPPMAIN_DEP)

   # Set files to be deleted by clean target
   GET_DIRECTORY_PROPERTY(DIRPROP ADDITIONAL_MAKE_CLEAN_FILES)
   SET(DIRDROP ${DIRDROP} ${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_NAME}.o ${ADDITIONAL_REMOVE})
   SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${DIRDROP}")  
   
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
   SET(PAROBJ)
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
      SET(TARGET_NAME "zz_objmap_${par}")
      SET(OBJMAP_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${par} -listlong >> ${POPCPPOBJMAP_OBJECTMAP})
      ADD_CUSTOM_TARGET(${TARGET_NAME} ALL
                        COMMAND ${OBJMAP_COMMAND}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        VERBATIM)
   ENDFOREACH(par ${PAROBJ})
   # Set files to be deleted by clean target
   GET_DIRECTORY_PROPERTY(DIRPROP ADDITIONAL_MAKE_CLEAN_FILES)
   SET(DIRDROP ${DIRDROP} ${CMAKE_CURRENT_SOURCE_DIR}/${POPCPPOBJMAP_OBJECTMAP})
   SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${DIRDROP}")

ENDMACRO(ADD_POPC_OBJMAP)


MACRO(ADD_POPC_RUN)
   PARSE_ARGUMENTS(POPCRUN
      "OBJECTMAP;TARGET;MAIN"
      ""
      ${ARGN}
   )
   IF(NOT POPCRUN_OBJECTMAP)
      SET(POPCRUN_OBJECTMAP obj.map)
   ENDIF()
   IF(NOT POPCRUN_TARGET)
      SET(POPCRUN_TARGET run)
   ENDIF()
   IF(NOT POPCRUN_MAIN)
      SET(POPCRUN_MAIN main)
   ENDIF()
   SET(RUN_COMMAND popcrun ${POPCRUN_OBJECTMAP} ./${POPCRUN_MAIN} ${POPCRUN_DEFAULT_ARGS})
   ADD_CUSTOM_TARGET(${POPCRUN_TARGET}
                     COMMAND ${RUN_COMMAND}
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
ENDMACRO(ADD_POPC_RUN)
