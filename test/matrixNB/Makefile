all: fast

fast:
	popcc -O1 -O2 -O3  -fforce-addr -fomit-frame-pointer -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc -object -O1 -O2 -O3 -fforce-addr -fomit-frame-pointer  -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc
	./MatWorker.obj -listlong > obj.map

slow:
	popcc -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc -object -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc
	./MatWorker.obj -listlong > obj.map

clean:
	rm -f *.obj MatMul *.o obj.map

run:
	popcrun obj.map ./MatMul 600 10 5 log
