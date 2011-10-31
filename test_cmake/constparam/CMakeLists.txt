#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-constparam NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-constparam POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc)
ADD_POPC_OBJECT(POPCobject.obj POPCobject.ph POPCobject.cc data.cc structdata.cc DEP main-constparam)
ADD_POPC_OBJMAP(POPCobject.obj NOT_APPEND)
