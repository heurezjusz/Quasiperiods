include makefile.inc

all: main.e main_nlogn.e

OBJS = combine.o pack.o ukkonen.o lcands.o
OBJS_N = maxgap.o rmcands.o $(OBJS)
OBJS_NLOGN = maxgap_nlogn.o rmcands_nlogn.o $(OBJS)

HEADERS = $(wildcard *.h)


%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

main.e: main.o $(OBJS_N) $(HEADERS)
	g++ main.o $(OBJS_N) -o $@ $(LFLAGS)

main_nlogn.e: main_nlogn.o $(OBJS_NLOGN) $(HEADERS)
	g++ main_nlogn.o $(OBJS_NLOGN) -o $@ $(LFLAGS)

clean:
	rm -rf *.o *.e


.PHONY: clean all

