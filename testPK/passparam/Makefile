main:
	popcc -o main POPCobject.ph POPCobject.cc data.cc structdata.cc main.cc

object:
	popcc -object -o POPCobject.obj  data.cc structdata.cc POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > objmap

run:
	popcrun objmap ./main

clean:
	rm -f *.o
	rm -f *.obj
	rm -f main
