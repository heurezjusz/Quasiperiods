include makefile.inc

OBJS = ukkonen.o partition.o

all: $(OBJS)

HEADERS = $(wildcard *.h)


%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@

clean:
	rm -rf *.o *.e


.PHONY: clean all

