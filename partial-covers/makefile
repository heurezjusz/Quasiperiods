include makefile.inc

OBJS = ukkonen.o partition.o hull.o algorithm.o cst.o

all: $(OBJS) slow_algorithm.e partial_covers_all.e

HEADERS = $(wildcard *.h)


partial_covers_all.e: $(OBJS)
	g++ main.cpp $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $@

%.e: %.cpp
	g++ $< $(CXXFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

clean:
	rm -rf *.o *.e


.PHONY: clean all

