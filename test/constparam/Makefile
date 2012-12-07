all: main object

main:
	popcc -noclean -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc

object:
	popcc -noclean -object -o POPCobject.obj  data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map

run:
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main

clean:
	rm -f *.o
	rm -f *.obj
	rm -f main
	rm -f ob*
	rm -f _popc*
	
debug: 
	../../parser/popcc -noclean -no-pipe -verbose -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc
	../../parser/popcc -noclean -verbose -object -o POPCobject.obj data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map
	
debug_spezial:
	../../parser/popcc -popcdir=../.. -popcpp=../../parser/popcpp -DHAVE_CONFIG_H -I. -I../.. -noclean -verbose -no-pipe -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc
	../../parser/popcc -popcdir=../.. -popcpp=../../parser/popcpp -noclean -verbose -no-pipe -object -o POPCobject.obj data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map
