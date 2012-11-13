all: main POPObject.obj

main: main.cc POPObject.ph POPObject.cc
	popcc -o main POPObject.ph POPObject.cc main.cc

POPObject.obj: POPObject.ph POPObject.cc
	popcc -object -o POPObject.obj POPObject.cc POPObject.ph
	
clean:
	rm -f *.o *.obj main obj.map _paroc*

run:	
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=main
