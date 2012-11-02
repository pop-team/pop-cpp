POPCC=../../parser/popcc
POPCPP=../../parser/popcpp
POPCPATH=../../
POPCLIB=-L../../lib/.libs/ -lparoc_common
POPCINCLUDE=-I../../include/
POPCCOMPILE=-popcdir=$(POPCPATH) -popcpp=$(POPCPP) $(POPCLIB) $(POPCINCLUDE)
all: app object

app:
	$(POPCC) $(POPCCOMPILE) -o main integer.ph integer.cc main.cc

object:
	$(POPCC) $(POPCCOMPILE) -object -o integer.obj integer.cc integer.ph main.cc

clean:
	rm -f *.o *.obj main obj.map _paroc* popc_mpi_communicator

run:
	cp ../../communicator/popc_mpi_communicator ./
	mpiexec -np 3 popc_mpi_communicator -app=./main  
