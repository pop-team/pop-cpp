all: server client

server: server.cpp combox.h combox.cpp
	g++ -o server server.cpp combox.cpp

client: client.cpp combox.h combox.cpp
	g++ -o client client.cpp combox.cpp

clean: 
	rm -rf client server

run: 
	./server
