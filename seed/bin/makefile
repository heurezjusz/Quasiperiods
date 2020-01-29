include ../makefile.inc

all: seed_lin.e seed_nlogn.e seed_imp.e seed_lin_int.e seed_nlogn_int.e seed_imp_int.e


seed_lin.e: main.o ../lib/kkrrw
	g++ main.o $(wildcard ../lib/kkrrw/*) -o $@ $(LFLAGS)

seed_nlogn.e: main.o ../lib/kkrrws
	g++ main.o $(wildcard ../lib/kkrrws/*) -o $@ $(LFLAGS)

seed_imp.e: main.o ../lib/imp
	g++ main.o $(wildcard ../lib/imp/*) -o $@ $(LFLAGS)

seed_imp_slow.e: main.o ../lib/imp_slow
	g++ main.o $(wildcard ../lib/imp_slow/*) -o $@ $(LFLAGS)


seed_lin_int.e: main_int.o ../lib/kkrrw
	g++ main_int.o $(wildcard ../lib/kkrrw/*) -o $@ $(LFLAGS)

seed_nlogn_int.e: main_int.o ../lib/kkrrws
	g++ main_int.o $(wildcard ../lib/kkrrws/*) -o $@ $(LFLAGS)

seed_imp_int.e: main_int.o ../lib/imp
	g++ main_int.o $(wildcard ../lib/imp/*) -o $@ $(LFLAGS)

seed_imp_slow_int.e: main_int.o ../lib/imp_slow
	g++ main_int.o $(wildcard ../lib/imp_slow/*) -o $@ $(LFLAGS)



../lib/%:
	make -C ../lib $(patsubst ../lib/%,%,$@)

clean:
	rm -f *.o *.e

.PHONY: all clean