test: main.o
	g++ -g -std=c++11 main.o -o test

main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp

PreconditionViolationException.o: PreconditionViolationException.h PreconditionViolationException.cpp
	g++ -g -std=c++0x -c PreconditionViolationException.cpp

clean:
	rm test *.o
