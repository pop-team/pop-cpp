FLAGS=-g
all: fast

fast:
	popcc ${FLAGS} -O1 -O2 -O3  -fomit-frame-pointer -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc ${FLAGS} -object -O1 -O2 -O3 -fomit-frame-pointer  -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc
	./MatWorker.obj -listlong > obj.map

slow:
	popcc ${FLAGS} -async-allocation -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc ${FLAGS} -async-allocation  -object -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc
	./MatWorker.obj -listlong > obj.map

clean:
	rm -f *.obj MatMul *.o obj.map

run:
	popcrun obj.map ./MatMul 600 10 5 log 1
