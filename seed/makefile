include makefile.inc

all: tree.e

OBJS = tree.o combine.o pack.o maxgap.o ukkonen.o lcands.o rmcands.o

HEADERS = tree.h combine.h pack.h maxgap.h ukkonen.h lcands.h rmcands.h

%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

tree.e: $(OBJS) $(HEADERS)
	g++ $(OBJS) -o $@ $(LFLAGS)

clean:
	rm -r $(OBJS) tree.e

