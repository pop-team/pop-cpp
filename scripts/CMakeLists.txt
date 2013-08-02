#configure
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popcrun.in ${CMAKE_CURRENT_SOURCE_DIR}/popcrun)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in.in ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in.in ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc_script_setup.in ${CMAKE_CURRENT_SOURCE_DIR}/popc_script_setup)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc_setup.in ${CMAKE_CURRENT_SOURCE_DIR}/popc_setup)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.csh.in ${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.csh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.sh.in ${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.sh)

#install to dir
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popcrun DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-xmpcc DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.csh DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.csh DESTINATION etc)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.sh DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-user-env.sh DESTINATION etc)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.sh DESTINATION etc)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc-runtime-env.in DESTINATION etc)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/SXXpopc.in DESTINATION sbin)
#delete SXXpopc after debug
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SXXpopc.in ${CMAKE_CURRENT_SOURCE_DIR}/SXXpopc)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/SXXpopc DESTINATION sbin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_script_setup DESTINATION sbin)
install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/popc_setup DESTINATION sbin)

