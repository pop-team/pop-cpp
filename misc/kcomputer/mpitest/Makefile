all: mpiprocess forked process

k:
	FCCpx -Xg -pthread -o onlythread onlythread.cpp

onlythread: 
	g++ -o onlythread onlythread.cpp

mpiprocess: mpiprocess.cpp
	mpic++ -o mpiprocess mpiprocess.cpp -lpthread

forkedprocess: forkedprocess.cpp
	g++ -o forkedprocess forkedprocess.cpp
run:
	mpiexec -np 2 mpiprocess
clean:
	rm -f mpiprocess forkedprocess
