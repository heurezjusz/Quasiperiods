include ../makefile

all: combine.o

combine.o: combine.hpp combine.cpp
	g++ combine.cpp $(CXXFLAGS) -c -o combine.o

clean:
	rm -f combine.o