#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-barrier NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_OBJECT(Barrier.ph Barrier.cc NOBROKER)
ADD_POPC_MAIN(main-barrier Barrier.stub.o worker.ph worker.cc main.cc DEP nobroker-Barrier.ph)
ADD_POPC_OBJECT(Cworker.obj Barrier.stub.o worker.cc worker.ph DEP main-barrier)
ADD_POPC_OBJECT(Barrier.obj Barrier.ph Barrier.cc DEP Cworker.obj)
ADD_POPC_OBJMAP(Cworker.obj Barrier.obj NOT_APPEND)
