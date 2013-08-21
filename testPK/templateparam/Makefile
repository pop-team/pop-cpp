main:
	popcc  -o main ClassA.cc X.cc parobject.ph parobject.cc main.cc
object:
	popcc -object -o parobject.obj ClassA.cc X.cc parobject.ph parobject.cc
	./parobject.obj -listlong > objmap

clean:
	rm -f *.o
	rm -f main
	rm -f *.obj

run:
	popcrun objmap ./main
