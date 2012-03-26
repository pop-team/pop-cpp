#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-exception NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-exception exception.ph exception.cc IOExceptions.cc main.cc)
ADD_POPC_OBJECT(exception.obj IOExceptions.cc exception.ph exception.cc DEP main-exception)
ADD_POPC_OBJMAP(exception.obj NOT_APPEND)
