all: fast

fast:
	popcc -pseudo-dynamic -verbose -cxx=mpicxx -cpp="mpicxx -E" -O1 -O2 -O3  -fforce-addr -fomit-frame-pointer -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc -pseudo-dynamic -verbose -cxx=mpicxx -cpp="mpicxx -E" -object -O1 -O2 -O3 -fforce-addr -fomit-frame-pointer  -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc


slow:
	popcc -pseudo-dynamic -verbose -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	popcc -pseudo-dynamic -verbose -object -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc

clean:
	rm -f *.obj MatMul *.o obj.map

run:
	mpiexec -np 1 ./MatMul 600 4 1 log : -np 1 $(POPC_MPIMANAGER) : -np 4 ./MatWorker.obj -mpi -object=MatWorker
