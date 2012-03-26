all: main object

main:
	popcc -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc

object:
	popcc -object -o POPCobject.obj  data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map

run:
	popcrun obj.map ./main

clean:
	rm -f *.o
	rm -f *.obj
	rm -f main
	rm -f obj.map
