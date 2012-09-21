#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-classparam NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-classparam classdata.cc data.cc ParObject.ph ParObject.cc main.cc)
ADD_POPC_OBJECT(ParObject-cp.obj classdata.cc data.cc ParObject.cc ParObject.ph DEP main-classparam)
ADD_POPC_OBJMAP(ParObject-cp.obj NOT_APPEND)
