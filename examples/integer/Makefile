POPCC=../../parser/popcc
POPCPP=../../parser/popcpp
POPCPATH=../..
CROSSCOMPILE=-cxx=FCCpx -Xg -pthread -cpp="FCCpx -E"
POPCCOMPILE=-noclean -popc-static -popcdir=$(POPCPATH) -popcpp=$(POPCPP) $(CROSSCOMPILE) -verbose

all: main integer.obj

main: main.cc integer.ph integer.cc
	$(POPCC) $(POPCCOMPILE) -o main integer.ph integer.cc main.cc 

integer.obj: integer.ph integer.cc
	$(POPCC) $(POPCCOMPILE) -object -o integer.obj integer.cc integer.ph 

clean:
	rm -f *.o *.obj main obj.map _paroc* popc_mpi_interconnector

run: main integer.obj
	cp ../../interconnector/popc_mpi_interconnector ./
	mpiexec -np 3 popc_mpi_interconnector -app=./main  
