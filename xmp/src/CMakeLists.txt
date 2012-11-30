include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(popc_advanced
  popc_group_interface.cpp
)


install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_group_interface.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_advanced.a DESTINATION lib)
