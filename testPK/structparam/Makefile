main:
	popcc -o main ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj  ParObject.cc ParObject.ph
	./ParObject.obj -listlong > objmap

clean:
	rm -f *.o *.obj main

run:
	popcrun objmap ./main
