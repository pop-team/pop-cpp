all: main object

main:
	popcc  -o main ClassA.cc X.cc parobject.ph parobject.cc main.cc
object:
	popcc -object -o parobject.obj ClassA.cc X.cc parobject.ph parobject.cc
	./parobject.obj -listlong > obj.map

clean:
	rm -f *.o main *.obj obj.map

run:
	popcrun obj.map ./main
