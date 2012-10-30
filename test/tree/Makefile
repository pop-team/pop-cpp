all: app object

app:
	popcc -o main tree.ph tree.cc main.cc 

object:
	popcc -object -o tree.obj tree.cc tree.ph
	./tree.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	mpiexec -np 2 ../../communicator/popc_mpi_communicator -app=./main 3 4

