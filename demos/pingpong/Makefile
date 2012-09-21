all: app object

app:
	popcc -o main pingpong.ph pingpong.cc main.cc

object:
	popcc -object -o pingpong.obj pingpong.cc pingpong.ph main.cc
	./pingpong.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
