all: app object

app:
	popcc -o main demopopc.ph demopopc.cc main.cc

object:
	popcc -object -o demopopc.obj demopopc.cc demopopc.ph main.cc
	./demopopc.obj -listlong > obj.map

clean:
	rm -f *.o *.obj main obj.map

run:
	popcrun obj.map ./main 2 localhost localhost
