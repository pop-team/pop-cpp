main:
	popcc -o main data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj data.cc ParObject.cc ParObject.ph

	./ParObject.obj -listlong > objmap

clean:
	rm -f *.o 
	rm -f *.obj
	rm -f main

run:
	popcrun objmap ./main
