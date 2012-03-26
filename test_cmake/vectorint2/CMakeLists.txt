#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-vectorint2 NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-vectorint2 popintvector.cc ParObject.ph ParObject.cc main.cc)
ADD_POPC_OBJECT(ParObject-vi2.obj popintvector.cc ParObject.cc ParObject.ph)
ADD_POPC_OBJMAP(ParObject-vi2.obj NOT_APPEND)
