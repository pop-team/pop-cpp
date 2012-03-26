#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-heritageparam2 NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-heritageparam2 heritdata.cc data.cc ParObject.ph ParObject.cc main.cc)
ADD_POPC_OBJECT(ParObject.obj heritdata.cc data.cc ParObject.cc ParObject.ph DEP main-heritageparam2)
ADD_POPC_OBJMAP(ParObject.obj NOT_APPEND)
