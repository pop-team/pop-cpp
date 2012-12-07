all: main application.obj radio.obj objmap

main: main.cpp radio.ph radio.cpp application.ph application.cpp
	popcc -parclass-nobroker -o main main.cpp radio.ph application.ph

application.obj: application.ph application.cpp
	popcc -object -o application.obj application.ph application.cpp

radio.obj: radio.ph radio.cpp
	popcc -object -o radio.obj radio.ph radio.cpp

objmap: radio.obj application.obj
	./radio.obj -listlong > obj.map
	./application.obj -listlong >> obj.map

run:
	popcrun obj.map ./main

clean:
	rm -f *.o *.obj main obj.map
