all: main sideprogram pthread

main: main.cpp
	g++ -o main main.cpp
sideprogram:
	g++ -o sideprogram sideprogram.cpp

pthread: pthread_example.cpp
	g++ -o pthread_example pthread_example.cpp
run:
	./main

clean: 
	rm -rf main sideprogram pthread_example
