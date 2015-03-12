FLAGS=-g
all: main object

main:
	popcc ${FLAGS} -o main classdata.cc data.cc ParObject.ph ParObject.cc main.cc

object:
	popcc ${FLAGS} -object -o ParObject.obj classdata.cc data.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
