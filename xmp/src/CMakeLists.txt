include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(popc_advanced
  popc_group_interface.cpp
  popc_group_broker.cpp
  popc_group_broker_factory.cpp
  popc_object.cpp
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_advanced_header.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_group_interface.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_group_broker.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_group_broker_factory.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/popc_object.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libpopc_advanced.a DESTINATION lib)
