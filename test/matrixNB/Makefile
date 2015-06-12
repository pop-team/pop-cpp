FLAGS=-g
all: fast

fast:
	popcc ${FLAGS} -O3  -fomit-frame-pointer -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc ${FLAGS} -object -O3 -fomit-frame-pointer  -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc
	./MatWorker.obj -listlong > obj.map

slow:
	popcc ${FLAGS} -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc ${FLAGS} -object -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc
	./MatWorker.obj -listlong > obj.map

clean:
	rm -f *.obj MatMul *.o obj.map

run:
	popcrun obj.map ./MatMul 600 10 5 log 1
