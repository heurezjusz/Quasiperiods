include makefile.inc

OBJS = ukkonen.o partition.o

all: $(OBJS) slow_algorithm.e

HEADERS = $(wildcard *.h)

%.e: %.cpp
	g++ $< $(CXXFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

clean:
	rm -rf *.o *.e


.PHONY: clean all

