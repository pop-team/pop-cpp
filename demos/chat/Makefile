all: app object

app:
	popcc -g -noclean -o main chat.ph chat.cc main.cc

object:
	popcc -g -noclean -object -o chat.obj chat.cc chat.ph main.cc
	./chat.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
