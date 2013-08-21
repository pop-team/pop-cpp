main:
	popcc -o main heritdata.cc data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj heritdata.cc data.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > objmap

clean:
	rm *.o *.obj main

run:
	popcrun objmap ./main
