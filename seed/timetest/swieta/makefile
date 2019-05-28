all: sommer.e gen.e

CXXFLAGS = -std=c++11 -W -Wall -g

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

sommer.e: sommer_main.cpp sommer.o
	g++ $^ $(CXXFLAGS) -o $@


gen.e: genword.o sommer.o
	g++ gen.cpp $^ $(CXXFLAGS) -o $@



clean:
	rm -f *.o *.e

.PHONY: clean
