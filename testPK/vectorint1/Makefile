main:
	popcc -o main popintvector.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj popintvector.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > objmap

clean:
	rm *.o *.obj main

run:
	popcrun objmap ./main
