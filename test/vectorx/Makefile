all: app object

app:
	popcc -o main popxvector.cc X.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj popxvector.cc X.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map


run:
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main
