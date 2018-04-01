include ../makefile.inc

all: structs.o

structs.o: structs.hpp structs.cpp
	g++ structs.cpp -std=c++11 -W -Wall -c -o $@

clean:
	rm -f structs.o