main:
	popcc -O1 -O2 -O3  -fforce-addr -fomit-frame-pointer -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc

object:
	popcc -object -O1 -O2 -O3 -fforce-addr -fomit-frame-pointer  -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc
	./MatWorker.obj -listlong > objmap

clean:
	rm -f *.obj
	rm -f MatMul
	rm -f *.o

run:
	popcrun objmap ./MatMul
