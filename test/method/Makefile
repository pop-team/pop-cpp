all: app object

app:
	popcc -o main method.ph method.cc main.cc 

object:
	popcc -object -o method.obj method.cc method.ph
	./method.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main	

