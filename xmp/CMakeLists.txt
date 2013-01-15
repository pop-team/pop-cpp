#
# POP-C++ 
# XMP support component and POP-C++ advanced library
# 
# AUTHOR: Valentin Clement
# DATE: 2012/11/29
#


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(src) 

get_directory_property(INCLUDE_PATH INCLUDE_DIRECTORIES)
add_custom_target(popc_objmain.xmp.o ALL
                  COMMAND ${MPI_CXX_COMPILER} -I${CMAKE_SOURCE_DIR}/include -I${CMAKE_CURRENT_SOURCE_DIR}/src -c popc_objmain.xmp.cc -o popc_objmain.xmp.o
                  DEPENDS popc_objmain.xmp.cc
                  COMMENT "Compile object main for XMP support")





install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_xmp.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_objmain.xmp.o DESTINATION lib)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "popc_objmain.xmp.o")
