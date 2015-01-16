#
# POP-C++
# Header installation process for pseudo-dynamic communication model
#
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

file(GLOB_RECURSE POPCC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

install(FILES ${POPCC_HEADERS} DESTINATION include/pseudodynamic)
