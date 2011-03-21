all: app object

app:
	popcc  -o main ClassA.cc X.cc transmissible.cc parobject.ph parobject.cc main.cc

object:
	popcc -object -o parobject.obj ClassA.cc X.cc parobject.ph parobject.cc
	./parobject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
