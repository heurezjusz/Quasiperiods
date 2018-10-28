include makefile.inc

all: seed_lin.e seed_nlogn.e

OBJS = combine.o pack.o ukkonen.o lcands.o main.o
OBJS_N = maxgap.o rmcands.o algorithm.o $(OBJS)
OBJS_NLOGN = maxgap_nlogn.o rmcands_nlogn.o algorithm_nlogn.o $(OBJS)

HEADERS = $(wildcard *.h)


main.o: main.cpp
	g++ $< $(CXXFLAGS) -c -o $@

algorithm_nlogn.o: algorithm_nlogn.cpp algorithm.h
	g++ $< $(CXXFLAGS) -c -o $@

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

seed_lin.e: main.o $(OBJS_N) $(HEADERS)
	g++ $(OBJS_N) -o $@ $(LFLAGS)

seed_nlogn.e: $(OBJS_NLOGN) $(HEADERS)
	g++ $(OBJS_NLOGN) -o $@ $(LFLAGS)

clean:
	rm -rf *.o *.e


.PHONY: clean all

