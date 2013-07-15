configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in.in ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.sh)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.sh DESTINATION etc)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcrun.in ${CMAKE_CURRENT_SOURCE_DIR}/popcrun)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcrun DESTINATION bin)

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-xmpcc DESTINATION bin)

