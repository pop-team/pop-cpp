all: app object

app: method.ph method.cc main.cc
	popcc -o main method.ph method.cc main.cc

object: method.cc method.ph
	popcc -object -o method.obj method.cc method.ph
	./method.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run: object app
	popcrun obj.map ./main
