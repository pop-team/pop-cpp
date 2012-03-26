#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-heritageparam1 NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_OBJECT(ParObject-hp1.obj heritdata.cc data.cc ParObject.cc ParObject.ph)
ADD_POPC_MAIN(main-heritageparam1 heritdata.cc data.cc ParObject.ph ParObject.cc main.cc DEP ParObject-hp1.obj)
ADD_POPC_OBJMAP(ParObject-hp1.obj NOT_APPEND)








