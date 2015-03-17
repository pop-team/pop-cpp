FLAGS=-g
all: main object

main:
	popcc ${FLAGS}  -o main ClassA.cc X.cc parobject.ph parobject.cc main.cc
object:
	popcc ${FLAGS} -object -o parobject.obj ClassA.cc X.cc parobject.ph parobject.cc
	./parobject.obj -listlong > obj.map

clean:
	rm -f *.o main *.obj obj.map

run:
	popcrun obj.map ./main
