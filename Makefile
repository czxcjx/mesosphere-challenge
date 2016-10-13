all:
	g++ -c src/control_system.cpp -o obj/control_system.o
	g++ obj/control_system.o src/main.cpp -o bin/main
