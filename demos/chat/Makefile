all: app object

app:
	popcc -o main chat.ph chat.cc main.cc

object:
	popcc -object -o chat.obj chat.cc chat.ph main.cc
	./chat.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
