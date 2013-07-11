configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun.in ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcobjrun DESTINATION services)

