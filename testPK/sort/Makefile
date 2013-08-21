main:
	popcc  -o main sortedlistclass.cc sortedlistclass.ph listclass.cc serializablelist.cc main.cc
object:
	popcc -object -o sortedlistclass.obj sortedlistclass.cc listclass.cc serializablelist.cc sortedlistclass.ph
	./sortedlistclass.obj -listlong > objmap

clean:
	rm -f *.o
	rm -f main
	rm -f *.obj

run:
	popcrun objmap ./main 1000003 5
