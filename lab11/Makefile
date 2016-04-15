test: main.o Box.o StackOfBoxes.o
	g++ -g -std=c++0x main.o Box.o StackOfBoxes.o -o test

main.o: main.cpp Box.h StackOfBoxes.h
	g++ -g -std=c++0x -c main.cpp

Box.o: Box.h Box.cpp
	g++ -g -std=c++0x -c Box.cpp
	
StackOfBoxes.o: StackOfBoxes.h StackOfBoxes.cpp
	g++ -g -std=c++0x -c StackOfBoxes.cpp
