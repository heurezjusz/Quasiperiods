include makefile.inc

all: tree.e

OBJS = tree.o combine.o structs.o ukkonen.o lcands.o rmcands.o

HEADERS = tree.hpp combine.hpp structs.hpp ukkonen.hpp lcands.hpp rmcands.hpp

%.o: %.cpp %.hpp
	g++ $< $(CXXFLAGS) -c -o $@

tree.e: $(OBJS) $(HEADERS)
	g++ $(OBJS) -o $@ $(LFLAGS)

clean:
	rm -r $(OBJS) tree.e

