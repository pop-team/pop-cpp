FLAGS=-g

all: main

main: main.cc
	popcc ${FLAGS} -o main main.cc

clean:
	rm -f *.o *.obj main obj.map

run: main
	./main
