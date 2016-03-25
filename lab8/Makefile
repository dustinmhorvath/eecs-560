test: main.o
	g++ -g -std=c++11 main.o -o test

main.o: main.cpp Heap.cpp
	g++ -g -std=c++11 -c main.cpp

Heap.o: Heap.h Heap.cpp
	g++ -g -std=c++0x -c Heap.cpp

clean:
	rm test *.o
