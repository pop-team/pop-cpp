FLAGS=-g
all: app object

app:
	popcc ${FLAGS} -o main tree.ph tree.cc main.cc 

object:
	popcc ${FLAGS} -object -o tree.obj tree.cc tree.ph
	./tree.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main 3 4

