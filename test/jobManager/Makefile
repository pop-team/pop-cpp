all: app object

app:
	popcc -o main POPCobject.ph POPCobject.cc main.cc

object:
	popcc -object -o POPCobject.obj POPCobject.ph POPCobject.cc
	./POPCobject.obj -listlong > obj.map

run:
	popcrun obj.map ./main 2 localhost localhost

clean:
	rm -f *.o *.obj main obj.map

