include ../makefile.inc

all: ukkonen.o

ukkonen.o: ukkonen.hpp ukkonen.cpp
	g++ ukkonen.cpp -std=c++11 -W -Wall -c -o $@

clean:
	rm -f ukkonen.o