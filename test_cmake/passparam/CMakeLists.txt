#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-passparam NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(main-passparam POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc)
ADD_POPC_OBJECT(POPCobject-passparam.obj POPCobject.ph POPCobject.cc data.cc structdata.cc)
ADD_POPC_OBJMAP(POPCobject-passparam.obj NOT_APPEND)
