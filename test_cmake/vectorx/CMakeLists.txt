#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-vectorx NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-vectorx popxvector.cc X.cc ParObject.ph ParObject.cc main.cc)
ADD_POPC_OBJECT(ParObject-vx.obj popxvector.cc X.cc ParObject.cc ParObject.ph)
ADD_POPC_OBJMAP(ParObject-vx.obj NOT_APPEND)
