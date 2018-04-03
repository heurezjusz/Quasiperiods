include ../makefile.inc

all: ukkonen.o

ukkonen.o: ukkonen.hpp ukkonen.cpp
	g++ ukkonen.cpp $(CXXFLAGS) -c -o $@

clean:
	rm -f ukkonen.o
