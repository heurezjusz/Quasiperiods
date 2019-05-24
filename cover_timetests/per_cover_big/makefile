all: ingen

SWIETA = sommer.o genword.o
include ../makefile.inc

swieta:
	make -C ../swieta $(SWIETA)
	cp ../swieta/sommer.o ../swieta/genword.o .
.PHONY: swieta

ingen.e: ingen.cpp swieta
	g++ $(CXXFLAGS) ingen.cpp $(SWIETA) -o $@ 

clean:
	rm -f *.o *.e
.PHONY: clean

ingen: ingen.e
	./ingen.e

clean-gen:
	rm -f *.in

.PHONY: ingen