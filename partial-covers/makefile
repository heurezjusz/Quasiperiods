include makefile.inc

OBJS = partition.o

OBJS_ALL = $(OBJS) algorithm_all.o hull.o ukkonen.o cst.o

OBJS_SINGLE = $(OBJS) algorithm_single.o ukkonen_leafs.o cst_leafs.o


all: slow_algorithm.e partial_covers_all.e partial_covers_single.e slow_algorithm_single.e detect.e

HEADERS = $(wildcard *.h)


detect.e: algorithm_main_detect.cpp ukkonen_leafs.o cst_leafs.o partition.o
	g++ -DADD_LEAF algorithm_main_detect.cpp ukkonen_leafs.o cst_leafs.o partition.o $(CXXFLAGS) $(LDFLAGS) -o $@

partial_covers_all.e: $(OBJS_ALL) main_all.cpp
	g++ main_all.cpp $(OBJS_ALL) $(CXXFLAGS) $(LDFLAGS) -o $@

partial_covers_single.e: $(OBJS_SINGLE) main_single.cpp
	g++ -DADD_LEAF main_single.cpp $(OBJS_SINGLE) $(CXXFLAGS) $(LDFLAGS) -o $@

ukkonen_leafs.o: ukkonen.cpp ukkonen.h
	g++ -DADD_LEAF $< $(CXXFLAGS) -c -o $@

cst_leafs.o: cst.cpp cst.h
	g++ -DADD_LEAF $< $(CXXFLAGS) -c -o $@

algorithm_single.o: algorithm_single.cpp algorithm_single.h
	g++ -DADD_LEAF $< $(CXXFLAGS) -c -o $@

%.e: %.cpp
	g++ $< $(CXXFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

clean:
	rm -rf *.o *.e


.PHONY: clean all
