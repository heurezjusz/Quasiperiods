include ../../makefile.inc

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(OBJS)

%.e: %.cpp
	g++ $< $(CXXFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

clean:
	rm -rf *.o *.e

.PHONY: clean all
