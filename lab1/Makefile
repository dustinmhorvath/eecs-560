test: main.o Node.o LinkedList.o
	g++ -g -std=c++11 main.o Node.o LinkedList.o -o test

main.o: main.cpp Node.h LinkedList.h
	g++ -g -std=c++11 -c main.cpp

Node.o: Node.h Node.cpp
	g++ -g -std=c++11 -c Node.cpp
	
LinkedList.o: LinkedList.h LinkedList.cpp
	g++ -g -std=c++11 -c LinkedList.cpp
