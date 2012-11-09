all: mpiprocess forkedprocess

mpiprocess: mpiprocess.cpp
	mpic++ -o mpiprocess mpiprocess.cpp

forkedprocess: forkedprocess.cpp
	g++ -o forkedprocess forkedprocess.cpp
run:
	mpiexec -np 2 mpiprocess
clean:
	rm -f mpiprocess forkedprocess
