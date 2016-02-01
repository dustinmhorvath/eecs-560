test: main.o Node.o BinarySearchTree.o
	g++ -g -std=c++11 main.o Node.o BinarySearchTree.o -o test

main.o: main.cpp Node.h BinarySearchTree.h
	g++ -g -std=c++11 -c main.cpp

Node.o: Node.h Node.cpp
	g++ -g -std=c++11 -c Node.cpp
	
BinarySearchTree.o: BinarySearchTree.h BinarySearchTree.cpp
	g++ -g -std=c++11 -c BinarySearchTree.cpp

clean:
	rm test *.o
