cmake_minimum_required(VERSION 2.4)

SET(VERSION_MAJOR 1 CACHE INTERNAL "")
SET(VERSION_MINOR 0 CACHE INTERNAL "")
SET(VERSION_PATCH 0 CACHE INTERNAL "")

PROJECT(test-integer NONE)
enable_language(POPCPP)

SET(CMAKE_VERBOSE_MAKEFILE on)




#SET(OBJECT_COMPILATION_FLAGS -object -o)
#SET(MAIN_COMPILATION_FLAGS -o)
#SET(OBJECT_MAP_FLAGS -listlong)
#SET(OBJECT_OUTPUT integer.obj)
#SET(OBJECT_MAP_FILE obj.map)

# Using standard CMake macro
#ADD_EXECUTABLE(integer integer_h.ph integer_c.cc)

SET(POPCPP_FLAGS -object -o)

# Using special Macro
ADD_PARALLEL_OBJECT(integer.obj integer_h.ph integer_c.cc)
ADD_POPCPP_MAIN(main main.cc integer_h.ph integer_c.cc)
OBJECT_MAP(integer.obj obj.map)







