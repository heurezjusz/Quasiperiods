include makefile.inc

all: main.e

OBJS = combine.o pack.o maxgap.o ukkonen.o lcands.o rmcands.o

HEADERS = tree.h combine.h pack.h maxgap.h ukkonen.h lcands.h rmcands.h

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

main.e: main.o $(OBJS) $(HEADERS)
	g++ main.o $(OBJS) -o $@ $(LFLAGS)

clean:
	rm -r $(OBJS) tree.e

nlogn:
	cp nlogn/maxgap.* nlogn/main.cpp .

lin:
	cp lin/maxgap.*  .

.PHONY: clean all nlogn lin

