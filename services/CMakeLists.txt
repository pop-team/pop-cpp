#
# POP-C++ 
# services components
# 
# AUTHOR: vanhieu.nguyen
# DATE: 2013/07/17
#

add_subdirectory(lib)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun.in ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun)

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun DESTINATION services)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/jobmgr.conf.in DESTINATION etc)

