all:
	g++ -c src/control_system.cpp -o obj/control_system.o
	g++ -c src/blank_module.cpp -o obj/blank_module.o
	g++ obj/control_system.o obj/blank_module.o src/main.cpp -o bin/main

clean:
	rm bin/* obj/*
