all: main

main: main.cpp
	mpic++ -o network-node main.cpp

run: main
	mpiexec	-np 2 network-node

clean:
	rm -rf network-node
