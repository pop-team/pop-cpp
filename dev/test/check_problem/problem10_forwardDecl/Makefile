all: app object

app:
	popcc -o main main.cc classA.cc classA.ph

object:
	popcc -object -o classA.obj classA.cc classA.ph
	./classA.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main
