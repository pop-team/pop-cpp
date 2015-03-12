POPCC=popcc
FLAGS=-pseudo-dynamic -verbose

all: main integer.obj

main: main.cc integer.ph integer.cc
	$(POPCC) $(FLAGS) -o main integer.ph integer.cc main.cc 

integer.obj: integer.ph integer.cc
	$(POPCC) $(FLAGS) -object -o integer.obj integer.cc integer.ph 

clean:
	rm -f *.o *.obj main obj.map _popc* popc_mpi_interconnector

run: main integer.obj
	cp ../../interconnector/popc_mpi_interconnector ./
	mpiexec -np 3 popc_mpi_interconnector -app=./main  
