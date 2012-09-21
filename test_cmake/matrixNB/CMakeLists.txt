#
# IF COMPILED ALONE, PLEASE UNCOMMENT THE THREE FOLLOWING LINES
#
#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#PROJECT(test-matrixNB NONE)
#ENABLE_LANGUAGE(POPCPP)

ADD_POPC_MAIN(MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc FLAGS -O1 -O2 -O3 -fforce-addr -fomit-frame-pointer -o)
ADD_POPC_OBJECT(MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc FLAGS -object -O1 -O2 -O3 -fforce-addr -fomit-frame-pointer -o)
ADD_POPC_OBJMAP(MatWorker.obj NOT_APPEND)
