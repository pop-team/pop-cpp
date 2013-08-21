main:
	popcc -o main popxvector.cc X.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj popxvector.cc X.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > objmap

clean:
	rm *.o *.obj main

run:
	popcrun objmap ./main
