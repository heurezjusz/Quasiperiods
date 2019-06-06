all: ingen

SWIETA = sommer.o genword.o
CXXFLAGS = -W -Wall -std=c++11 -g

swieta:
	make -C ../swieta $(SWIETA)
	cp ../swieta/sommer.o ../swieta/genword.o .
.PHONY: swieta

gen.e: gen.cpp swieta
	g++ $(CXXFLAGS) gen.cpp $(SWIETA) -o $@

clean:
	rm -f *.o *.e
.PHONY: clean

ingen:
	make gen.e
	./gen.e
	make clean

clean-gen:
	rm -f *.in

.PHONY: ingen
