POPCC=../../parser/popcc
POPCPP=../../parser/popcpp
POPCPATH=../../
POPCLIB=-L../../lib/.libs/ -lparoc_common
POPCINCLUDE=-I../../include/
POPCCOMPILE=-popcdir=$(POPCPATH) -popcpp=$(POPCPP) $(POPCLIB) $(POPCINCLUDE)
all: main integer.obj

main: main.cc integer.ph integer.cc
	$(POPCC) $(POPCCOMPILE) -o main integer.ph integer.cc main.cc

integer.obj: integer.ph integer.cc
	$(POPCC) $(POPCCOMPILE) -object -o integer.obj integer.cc integer.ph

clean:
	rm -f *.o *.obj main obj.map _paroc* popc_mpi_communicator

run: main integer.obj
	cp ../../communicator/popc_mpi_communicator ./
	mpiexec -np 3 popc_mpi_communicator -app=./main  
