all: main testmpi.obj objmap

main: main.cc testmpi.ph testmpi.cc
	popcc -cxx=mpic++ -cpp="mpic++ -E"  -o main main.cc testmpi.ph testmpi.cc

testmpi.obj: testmpi.ph testmpi.cc
	popcc -noclean -cxx=mpic++ -cpp="mpic++ -E" -object=mpi -o testmpi.obj testmpi.ph testmpi.cc

objmap: testmpi.obj 
	./testmpi.obj -listlong > obj.map

run: main testmpi.obj
	popcrun obj.map ./main

clean: 
	rm -rf *.o _paroc* obj.map main testmpi.obj
