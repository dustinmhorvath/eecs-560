test: main.o
	g++  -pg -std=c++11 main.o -o test

main.o: main.cpp
	g++  -pg -std=c++11 -c main.cpp

PreconditionViolationException.o: PreconditionViolationException.h PreconditionViolationException.cpp
	g++  -pg -std=c++0x -c PreconditionViolationException.cpp

clean:
	rm test *.o
