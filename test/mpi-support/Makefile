all: main mpiobject.obj

main: main.cpp mpiobject.ph mpiobject.cpp
	popcc -mpi -popc-static -o main main.cpp mpiobject.ph mpiobject.cpp

mpiobject.obj: mpiobject.ph mpiobject.cpp
	popcc -mpi -popc-static -object -o mpiobject.obj mpiobject.ph mpiobject.cpp

run: main mpiobject.obj
	mpiexec -np 1 $(POPC_INTERCONNECTOR) -app=./main

clean: 
	rm -f main *.o *.obj _popc*
