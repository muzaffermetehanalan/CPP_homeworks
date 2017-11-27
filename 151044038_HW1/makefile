all: main

main: main.o
	g++ main.o -o mycpu

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o main
