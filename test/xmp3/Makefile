all: main xmp.o

xmp.o: xmp.c
	gcc -c xmp.c

main: main.cpp xmp.o
	popcc -o main main.cpp xmp.o

clean: 
	rm -f *.o main
