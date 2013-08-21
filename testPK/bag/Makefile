main:
	popcc -async-allocation -o main Bag.ph Bag.cc main.cc

object:
	popcc -async-allocation -object -o bag.obj Bag.ph Bag.cc
	./bag.obj -listlong > objmap

clean:
	rm -f *.o
	rm -f *.obj

	rm -f main

run:
	popcrun objmap ./main
