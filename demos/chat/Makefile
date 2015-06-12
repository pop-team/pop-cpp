POP_FLAGS =-g ${FLAGS}

all: app object

app:
	popcc ${POP_FLAGS} -o main chat.ph chat.cc main.cc

object:
	popcc ${POP_FLAGS} -object -o chat.obj chat.cc chat.ph main.cc
	./chat.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
