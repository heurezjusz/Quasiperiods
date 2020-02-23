include makefile.inc

OBJS = partition.o

OBJS_ALL = $(OBJS) algorithm_all.o hull.o ukkonen.o cst.o

OBJS_SINGLE = $(OBJS) algorithm_single.o ukkonen_leafs.o cst_leafs.o


all: slow_algorithm.e partial_covers_all.e partial_covers_single.e slow_algorithm_single.e

HEADERS = $(wildcard *.h)


partial_covers_all.e: $(OBJS_ALL) main_all.cpp
	g++ main_all.cpp $(OBJS_ALL) $(CXXFLAGS) $(LDFLAGS) -o $@

partial_covers_single.e: $(OBJS_SINGLE) main_single.cpp
	g++ main_single.cpp $(OBJS_SINGLE) $(CXXFLAGS) $(LDFLAGS) -o $@

%.e: %.cpp
	g++ $< $(CXXFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

clean:
	rm -rf *.o *.e


.PHONY: clean all
