main:
	popcc -o main popcfactoriel.ph popcfactoriel.cc main.cc

object:
	popcc -object -o popcfactoriel.obj popcfactoriel.ph popcfactoriel.cc
	./popcfactoriel.obj -listlong > objmap

run:
	popcrun objmap ./main

clean:
	rm -f *.o
	rm -f *.obj
	rm -f main
