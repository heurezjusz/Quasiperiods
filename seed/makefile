include makefile.inc

all: tree.e

OBJS = tree.o combine.o structs.o ukkonen.o lcands.o

HEADERS = tree.hpp combine.hpp structs.hpp ukkonen.hpp lcands.hpp

%.o: %.cpp %.hpp
	g++ $< $(CXXFLAGS) -c -o $@

tree.e: $(OBJS) $(HEADERS)
	g++ $^ -o $@ $(LFLAGS)

clean:
	rm -r $(OBJS) tree.e

