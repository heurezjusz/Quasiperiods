all: sommer.e

CXXFLAGS = -std=c++11 -W -Wall -g

sommer.o: sommer.cpp sommer.h
	g++ $< $(CXXFLAGS) -c -o sommer.o

sommer.e: sommer_main.cpp sommer.o
	g++ $^ $(CXXFLAGS) -o $@

%.e: %.cpp
	g++ $< -o $@ $(CXXFLAGS)

clean:
	rm -f *.o *.e
.PHONY: clean