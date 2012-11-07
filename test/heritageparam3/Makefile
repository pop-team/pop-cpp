all: main object

main:
	popcc -o main heritdata.cc data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -noclean -object -o ParObject.obj heritdata.cc data.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > objmap

clean:
	rm -f *.o *.obj main objmap _paroc*

run:
	mpiexec -np 2 ../../interconnector/popc_mpi_interconnector -app=./main
