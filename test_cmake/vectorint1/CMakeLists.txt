#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-vectorint1 NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-vectorint1 popintvector.cc ParObject.ph ParObject.cc main.cc)
ADD_POPC_OBJECT(ParObject-vi1.obj popintvector.cc ParObject.cc ParObject.ph)
ADD_POPC_OBJMAP(ParObject-vi1.obj NOT_APPEND)
