include ../makefile.inc

all: partial_covers_all.e partial_covers_single.e


partial_covers_all.e: main_all.o ../lib/algorithm_all
	g++ main_all.o $(wildcard ../lib/algorithm_all/*) -o $@ $(LFLAGS)

partial_covers_single.e: main_single.o ../lib/algorithm_single
	g++ main_single.o $(wildcard ../lib/algorithm_single/*) -o $@ $(LFLAGS)

../lib/%:
	make -C ../lib $(patsubst ../lib/%,%,$@)


clean:
	rm -f partial_covers_all.e partial_covers_single.e

.PHONY: clean all
