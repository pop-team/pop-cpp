FLAGS=-g
all: app object

app:
	popcc ${FLAGS} -o main popintvector.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc ${FLAGS} -object -o ParObject.obj popintvector.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
