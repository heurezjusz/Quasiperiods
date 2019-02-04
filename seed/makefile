include makefile.inc

all: seed_lin.e seed_nlogn.e seed_costas.e

OBJS = combine.o pack.o ukkonen.o lcands.o main.o
OBJS_N = maxgap.o rmcands.o rmcands_lens.o rmcands_16.o algorithm.o $(OBJS)
OBJS_NLOGN = maxgap_nlogn.o rmcands_nlogn.o algorithm_nlogn.o $(OBJS)

OBJS_COSTAS = main.o pack.o algorithm_costas.o

HEADERS = $(wildcard *.h)

rmcands_lens.o: rmcands.cpp rmcands_lens.h
	g++ $< $(CXXFLAGS) -DLENS -c -o $@

rmcands_16.o: rmcands.cpp rmcands16.h
	g++ $< $(CXXFLAGS) -DMX16 -c -o $@

main.o: main.cpp
	g++ $< $(CXXFLAGS) -c -o $@

algorithm_nlogn.o: algorithm_nlogn.cpp algorithm.h
	g++ $< $(CXXFLAGS) -c -o $@

algorithm_costas.o: algorithm_costas.cpp algorithm.h
	g++ $< $(CXXFLAGS) -c -o $@


%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

seed_lin.e: main.o $(OBJS_N) $(HEADERS)
	g++ $(OBJS_N) -o $@ $(LFLAGS)

seed_nlogn.e: $(OBJS_NLOGN) $(HEADERS)
	g++ $(OBJS_NLOGN) -o $@ $(LFLAGS)

seed_costas.e: $(OBJS_COSTAS) $(HEADERS)
	g++ $(OBJS_COSTAS) -o $@ $(LFLAGS)

clean:
	rm -rf *.o *.e


.PHONY: clean all

