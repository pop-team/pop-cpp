# 
# AUTHOR: Valentin Clement
# DATE: 2012/11/29
#
# Copyright (c) 2005-2012 POP-C++ project - GRID and Cloud Computing Group, University of applied Science of western Switzerland  
#
#
# Specific compilation and install instrcution for XMP support for POP-C++
#
# To enable XMP support in the compilation process use -DXMP_SUPPORT=ON with the cmake command
#
#

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)


get_directory_property(INCLUDE_PATH INCLUDE_DIRECTORIES)
add_custom_target(popc_objmain.xmp.o ALL
                  COMMAND ${MPI_COMPILER} -I${INCLUDE_PATH} -c popc_objmain.xmp.cc -o popc_objmain.xmp.o
                  DEPENDS popc_objmain.xmp.cc
                  COMMENT "Compile object main for XMP support")





install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_xmp.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_objmain.xmp.o DESTINATION lib)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "popc_objmain.xmp.o")
