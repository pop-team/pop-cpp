
find_package(CxxTest)

set(POPCPP_FLAGS ${POPCPP_EXTRA_FLAGS} -cpp11 -popcpp-compilation -no-implicit-pack -popcdir=${CMAKE_SOURCE_DIR} -popcpp=${CMAKE_POPCPP_COMPILER})


add_definitions(-std=c++11)
link_directories(${CMAKE_SOURCE_DIR}/lib/core ${CMAKE_SOURCE_DIR}/lib/dynamic)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpopc_core -lpopc_common -lpopc_core -lpopc_common" )

if(CXXTEST_FOUND)
	file(GLOB tests_src1 "*.test.h")

	add_executable(unitTests unitTests.cpp)
	target_link_libraries(unitTests popc_common popc_core popc_common popc_core pthread)

	add_custom_command(
		OUTPUT unitTests.cpp
		DEPENDS ${tests_src1}
		COMMAND cxxtestgen -o unitTests.cpp ${tests_src1} --xunit-printer
	)
else()
	message(WARNING "CxxTest library not found on your system. Unit tests will not be added to the project.")
endif()

add_custom_target(run ./unitTests)
