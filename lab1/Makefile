Lab1: main.o Box.o LinkedList.o
	g++ -g -std=c++0x main.o Box.o LinkedList.o -o Lab1

main.o: main.cpp Box.h LinkedList.h
	g++ -g -std=c++0x -c main.cpp

Box.o: Box.h Box.cpp
	g++ -g -std=c++0x -c Box.cpp
	
LinkedList.o: LinkedList.h LinkedList.cpp
	g++ -g -std=c++0x -c LinkedList.cpp
