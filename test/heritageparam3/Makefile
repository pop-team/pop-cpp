FLAGS=-g
all: main object

main:
	popcc ${FLAGS} -o main heritdata.cc data.cc ParObject.ph ParObject.cc main.cc 

object:
	popcc ${FLAGS} -object -o ParObject.obj heritdata.cc data.cc ParObject.cc ParObject.ph
	./ParObject.obj -listlong > objmap

clean:
	rm -f *.o *.obj main objmap

run:
	popcrun objmap ./main
