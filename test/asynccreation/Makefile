all: app object

noasync:
	popcc -noclean -no-async-allocation -o main POPObject.ph POPObject.cc main.cc
	popcc -noclean -no-async-allocation -object -o POPObject.obj POPObject.cc POPObject.ph main.cc 

app:
	popcc -noclean -o main POPObject.ph POPObject.cc main.cc

object:
	popcc -noclean -object -o POPObject.obj POPObject.cc POPObject.ph main.cc
	
clean:
	rm -f *.o *.obj main obj.map _popc*

run:
	mpiexec -np 1 ../../interconnector/popc_mpi_interconnector -app=./main
