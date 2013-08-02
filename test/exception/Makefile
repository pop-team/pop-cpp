all: main object

main:
	popcc -o main exception.ph exception.cc IOExceptions.cc main.cc

object:
	popcc -object -o exception.obj IOExceptions.cc exception.ph exception.cc
	./exception.obj -listlong > obj.map

clean:
	rm -f *.o _p*.* *.obj main obj.map

run:
	mpiexec -np 2 $(POPC_INTERCONNECTOR) -app=./main

