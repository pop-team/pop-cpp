all: app object

app:
	popcc -o main integer.ph integer.cc main.cc

object:
	popcc -object -o integer.obj integer.cc integer.ph main.cc

clean:
	rm -f *.o *.obj main obj.map _paroc*

run:
	mpiexec -np 2 ../../communicator/popc_mpi_communicator -app=./main 1 
