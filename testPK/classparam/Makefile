main:
	popcc -o main classdata.cc data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj classdata.cc data.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > objmap

clean:
	rm -f *.o *.obj main

run:
	popcrun objmap ./main
