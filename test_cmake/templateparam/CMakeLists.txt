#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-templateparam NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-templateparam ClassA.cc X.cc parobject.ph parobject.cc main.cc)
ADD_POPC_OBJECT(parobject-tp.obj ClassA.cc X.cc parobject.ph parobject.cc)
ADD_POPC_OBJMAP(parobject-tp.obj NOT_APPEND)
