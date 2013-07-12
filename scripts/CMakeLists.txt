configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.sh)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.sh DESTINATION etc)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcrun.in ${CMAKE_CURRENT_SOURCE_DIR}/popcrun)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcrun DESTINATION bin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SXXpopc.in ${CMAKE_CURRENT_SOURCE_DIR}/SXXpopc)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/SXXpopc DESTINATION sbin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc_setup.in ${CMAKE_CURRENT_SOURCE_DIR}/popc_setup)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_setup DESTINATION sbin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc_script_setup.in ${CMAKE_CURRENT_SOURCE_DIR}/popc_script_setup)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_script_setup DESTINATION sbin)

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-xmpcc DESTINATION bin)

