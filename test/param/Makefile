all: app object

app:
	popcc -o main data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc -object -o ParObject.obj data.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
