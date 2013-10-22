all: main spawned

main:main.cc
	mpic++ -o main main.cc

spawned:spawned.cc
	mpic++ -o spawned spawned.cc

clean: 
	rm -f main spawned

run: main spawned
	mpiexec -np 1 ./main
