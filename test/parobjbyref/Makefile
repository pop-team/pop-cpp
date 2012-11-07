all: app object

app:
	popcc -noclean -o main POPObject.ph POPObject.cc main.cc

object:
	popcc -noclean -object -o POPObject.obj POPObject.cc POPObject.ph main.cc
	./POPObject.obj -listlong > obj.map
	
clean:
	rm -f *.o *.obj main obj.map _paroc*

run:
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main
