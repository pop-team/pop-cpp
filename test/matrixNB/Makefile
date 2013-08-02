POPCC=popcc
POPCPP=popcpp
CROSSCOMPILE=-cxx=FCCpx -Xg -pthread -cpp="FCCpx -E"
POPCCOMPILE=-popc-static 

NODE_NUMBER=2

all: fast

fast:
	$(POPCC) $(POPCCOMPILE) -O3 -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	$(POPCC) $(POPCCOMPILE) -object -O3 -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc

slow:
	$(POPCC) $(POPCCOMPILE) -o MatMul Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc main.cc
	$(POPCC) $(POPCCOMPILE) -object -o MatWorker.obj Matrix2D.cc Matrix2Dlc.cc Matrix2Dcl.cc MatWorker.ph MatWorker.cc

clean:
	rm -f *.obj MatMul *.o obj.map

run:
	mpiexec -np $(NODE_NUMBER) $(POPC_INTERCONNECTOR) -app=MatMul 1200 16 1 log 1
