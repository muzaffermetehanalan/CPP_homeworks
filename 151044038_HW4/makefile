all: hw4

hw4: main.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ -std=c++11 main.o CPU.o CPUProgram.o Memory.o Computer.o -o hw4

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

CPU.o: CPU.cpp
	g++ -std=c++11 -c CPU.cpp

CPUProgram.o: CPUProgram.cpp
	g++ -std=c++11 -c CPUProgram.cpp

Memory.o: Memory.cpp
	g++ -std=c++11 -c Memory.cpp

Computer.o: Computer.cpp
	g++ -std=c++11 -c Computer.cpp

clean:
	rm *.o hw4
