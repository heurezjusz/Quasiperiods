include ../makefile.inc

all: utils.o

utils.o: utils.hpp utils.cpp
	g++ utils.cpp $(CXXFLAGS) -c -o utils.o

clean:
	rm -f utils.o