FLAGS=-g
all: main object

main:
	popcc ${FLAGS} -o main ParObject.ph ParObject.cc main.cc 

object:
	popcc ${FLAGS} -object -o ParObject.obj  ParObject.cc ParObject.ph
	./ParObject.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
