#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-param NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-param data.cc ParObject.ph ParObject.cc main.cc)
ADD_POPC_OBJECT(ParObject-param.obj data.cc ParObject.cc ParObject.ph)
ADD_POPC_OBJMAP(ParObject-param.obj NOT_APPEND)
