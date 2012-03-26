#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-callback NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_OBJECT(toto.ph toto.cc NOBROKER)
ADD_POPC_MAIN(main-callback toto.stub.o titi.ph titi.cc main.cc DEP nobroker-toto.ph)
ADD_POPC_OBJECT(titi.obj toto.stub.o titi.cc titi.ph DEP main-callback)
ADD_POPC_OBJECT(titi.ph titi.cc NOBROKER DEP titi.obj)
ADD_POPC_OBJECT(toto.obj titi.stub.o toto.cc toto.ph DEP nobroker-titi.ph)
ADD_POPC_OBJMAP(toto.obj titi.obj NOT_APPEND)
