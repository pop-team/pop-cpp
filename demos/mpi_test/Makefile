#INC_FLAGS=-I/opt/mpi/include/
INC_FLAGS=-I/usr/include/mpi/
MPICXX=mpicxx

#POPCDIR=/usr/local/popc
#INSTDIR=$(POPCDIR)/test/mpi_test
POP=popcc

all: TestMPI.obj main obj.map

main.o: 
	${POP} -c main.cc ${INC_FLAGS}

TestMPI.o:
	${POP} -c TestMPI.cc ${INC_FLAGS}

TestMPI.stub.o:
	${POP} -c TestMPI.ph ${INC_FLAGS}

main: main.o TestMPI.stub.o TestMPI.o
	${POP} -cxx=${MPICXX} -o main main.o TestMPI.stub.o TestMPI.o

TestMPI.obj: TestMPI.o TestMPI.stub.o
	${POP} -object=mpi -cxx=${MPICXX} -o TestMPI.obj TestMPI.o TestMPI.stub.o


clean:
	rm -f *.o *.obj main obj.map

#install: all 
#	@if [ ! -d $(INSTDIR)/ ]; then mkdir $(INSTDIR)/; fi
#	cp *.obj main  $(INSTDIR)/

obj.map: TestMPI.obj
	./TestMPI.obj -listlong > obj.map

run: TestMPI.obj main obj.map
	popcrun obj.map ./main
