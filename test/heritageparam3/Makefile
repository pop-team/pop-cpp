all: main object

main:
	popcc -o main heritdata.cc data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -noclean -object -o ParObject.obj heritdata.cc data.cc ParObject.cc ParObject.ph

clean:
	rm -f *.o *.obj main objmap _popc*

run:
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main
