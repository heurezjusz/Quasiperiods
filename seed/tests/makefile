include ../makefile.inc
CXXFLAGS += -g
DEP = $(wildcard ../lib/src/*.cpp ../lib/src/*.h)

make_sup: $(DEP)
	make -C ..
.PHONY: make_sup


# target: combine

combine: combine.e combine_slow.e packs_chk.e
.PHONY: combine

combine_slow.o: combine_slow.cpp ../lib/src/combine.h
	g++ combine_slow.cpp $(CXXFLAGS) -c -o $@

combine.o: combine.cpp ../lib/src/combine.h
	g++ combine.cpp $(CXXFLAGS) -c -o $@

combine.e: combine.o make_sup
	g++ combine.o ../lib/src/ukkonen.o ../lib/src/combine.o -o $@ $(LFLAGS)


# target: combine2

combine2: combine2.e combine2_slow.e packs_chk.e
.PHONY: combine2

combine2_slow.o: combine2_slow.cpp ../lib/src/combine.h
	g++ combine2_slow.cpp $(CXXFLAGS) -c -o $@

combine2.o: combine2.cpp ../lib/src/combine.h
	g++ combine2.cpp $(CXXFLAGS) -c -o $@

combine2.e: combine2.o make_sup
	g++ combine2.o ../lib/src/ukkonen.o ../lib/src/combine.o -o $@ $(LFLAGS)


# target: maxgap
maxgap: maxgap_slow.e maxgap.e
.PHONY: maxgap

maxgap_slow.e: maxgap_slow.cpp ../lib/src/pack.h
	g++ maxgap_slow.cpp $(CXXFLAGS) -o $@

maxgap.o: maxgap.cpp
	g++ maxgap.cpp -std=c++11 -W -Wall -c -o $@

maxgap.e: maxgap.o make_sup
	g++ maxgap.o ../lib/src/maxgap.o ../lib/src/pack.o -o $@ $(LFLAGS)


# target: maxgap_nlogn
maxgap_nlogn: maxgap_nlogn_slow.e maxgap_nlogn.e
.PHONY: maxgap_nlogn

maxgap_nlogn_slow.e: maxgap_nlogn_slow.cpp
	g++ maxgap_nlogn_slow.cpp $(CXXFLAGS) -o $@

maxgap_nlogn.o: maxgap_nlogn.cpp
	g++ maxgap_nlogn.cpp -std=c++11 -W -Wall -c -o $@

maxgap_nlogn.e: maxgap_nlogn.o make_sup
	g++ maxgap_nlogn.o ../lib/src/maxgap_nlogn.o -o $@ $(LFLAGS)


# target: ukkonen
ukkonen: ukkonen.e
.PHONY: ukkonen

ukkonen.o: ukkonen.cpp
	g++ ukkonen.cpp $(CXXFLAGS) -c -o $@
ukkonen.e: ukkonen.o make_sup
	g++ ukkonen.o ../lib/src/ukkonen.o -o $@ $(LFLAGS)


# target: ukkonen_perf
ukkonen_perf: ukkonen_perf.e ukkonen_perf_slow.e
.PHONY: ukkonen_perf

ukkonen_perf.o: ukkonen_perf.cpp
	g++ ukkonen_perf.cpp $(CXXFLAGS) -c -o $@

ukkonen_perf.e: ukkonen_perf.o make_sup
	g++ ukkonen_perf.o ../lib/src/ukkonen.o -o $@ $(LFLAGS)

ukkonen_perf_slow.o: ukkonen_perf_slow.cpp
	g++ ukkonen_perf_slow.cpp $(CXXFLAGS) -c -o $@

ukkonen_perf_slow.e: ukkonen_perf_slow.o make_sup
	g++ ukkonen_perf_slow.o ../lib/src/ukkonen.o -o $@ $(LFLAGS)


# target: lcands
lcands: lcands.e packs_chk.e
.PHONY: lcands

lcands.e: make_sup lcands.o
	g++ lcands.o ../lib/src/lcands.o -o $@ $(LFLAGS)


# target: rmcands
rmcands: rmcands.e rmcands_chk.e
.PHONY: rmcands

rmcands_chk.e: rmcands_chk.cpp
	g++ rmcands_chk.cpp -o $@ $(CXXFLAGS)

rmcands.e: make_sup rmcands.o
	g++ rmcands.o ../lib/src/rmcands.o ../lib/src/ukkonen.o ../lib/src/pack.o ../lib/src/maxgap.o -o $@ $(LFLAGS)


# target: rmcands_nlogn
rmcands_nlogn: rmcands_nlogn.e rmcands_chk.e
.PHONY: rmcands_nlogn

rmcands_nlogn.e: make_sup rmcands_nlogn.o
	g++ rmcands_nlogn.o ../lib/src/rmcands_nlogn.o ../lib/src/ukkonen.o ../lib/src/pack.o ../lib/src/maxgap_nlogn.o -o $@ $(LFLAGS)


#target: seeds_nlogn
seeds_nlogn: packs_chk.e seeds_nlogn.e
.PHONY: seeds_nlogn

seeds_nlogn.e: make_sup
	cp ../bin/seed_nlogn.e seeds_nlogn.e

#target: seeds
seeds: seeds_lin.e packs_chk.e
.PHONY: seeds

seeds_lin.e: make_sup
	cp ../bin/seed_lin.e seeds_lin.e

#target: lens
lens: lens.e
.PHONY: lens

lens.e: make_sup lens.o
	g++ lens.o ../lib/src/rmcands_lens.o ../lib/src/maxgap.o ../lib/src/ukkonen.o ../lib/src/pack.o -o $@ $(LFLAGS)

#target: choose_sub
choose_sub: choose_sub.e
.PHONY: choose_sub

choose_sub.e: make_sup choose_sub.o
	g++ choose_sub.o ../lib/src/ukkonen.o -o $@ $(LFLAGS)


#target: call_smaller
call_smaller: call_smaller.e
.PHONY: call_smaller

call_smaller.e: make_sup call_smaller.o
	g++ call_smaller.o ../lib/src/ukkonen.o ../lib/src/pack.o ../lib/src/combine.o -o $@ $(LFLAGS)


#target: call_parts
call_parts: call_parts.e
.PHONY: call_parts

call_parts.e: make_sup call_parts.o
	g++ call_parts.o ../lib/src/ukkonen.o ../lib/src/pack.o ../lib/src/combine.o -o $@ $(LFLAGS)


#target: seeds_vs
seeds_vs: seeds_lin.e seeds_nlogn.e packs_chk_combine.e
.PHONY: seeds_vs


#target: seeds_vs_big
seeds_vs_big: seeds_vs
.PHONY: seeds_vs_big


#target: seeds_imp_slow
seeds_imp_slow.e: make_sup
	make -C ../bin seed_imp_slow.e
	cp ../bin/seed_imp_slow.e seeds_imp_slow.e

seeds_imp_slow: packs_chk_imp.e seeds_imp_slow.e seeds_nlogn.e
.PHONY: seeds_imp_slow


#target: seeds_imp
seeds_imp.e: make_sup
	cp ../bin/seed_imp.e seeds_imp.e

seeds_imp: packs_chk_imp.e seeds_imp.e seeds_nlogn.e
.PHONY: seeds_imp


#target: seeds_imp_int
seeds_nlogn_int.e: make_sup
	cp ../bin/seed_nlogn_int.e seeds_nlogn_int.e

seeds_imp_int.e: make_sup
	cp ../bin/seed_imp_int.e seeds_imp_int.e

seeds_imp_int: packs_chk_imp_int.e seeds_imp_int.e seeds_nlogn_int.e
.PHONY: seeds_imp_int

#target: seeds_imp_slow_int
seeds_imp_slow_int.e:
	make -C ../bin seed_imp_slow_int.e
	cp ../bin/seed_imp_slow_int.e seeds_imp_slow_int.e

seeds_imp_slow_int: packs_chk_imp_int.e seeds_imp_slow_int.e seeds_nlogn_int.e
.PHONY: seeds_imp_slow_int

#target: seeds_imp_int_alot
seeds_imp_int_alot: seeds_imp_int
.PHONY: seeds_imp_int_alot

#target: seeds_imp_slow_int_alot
seeds_imp_slow_int_alot: seeds_imp_int
.PHONY: seeds_imp_slow_int_alot


#target: seeds_vs_int_alot
seeds_lin_int.e: make_sup
	cp ../bin/seed_lin_int.e seeds_lin_int.e

seeds_vs_int_alot: seeds_nlogn_int.e seeds_lin_int.e packs_chk_imp_int.e
.PHONY: seeds_imp_int_alot


#target: *.e
%.e: %.o
	g++ $^ -o $@ $(LFLAGS)

#target: packs_chk_diff.e
packs_chk_diff.e: packs_chk_diff.o
	g++ packs_chk_diff.o -o $@ $(LFLAGS)


#target: packs_chk_combine.e
packs_chk_combine.e: packs_chk_combine.o make_sup
	g++ packs_chk_combine.o ../lib/src/combine.o ../lib/src/ukkonen.o ../lib/src/pack.o -o $@ $(LFLAGS)

clean:
	rm -f *.o
	rm -f *.e
	make clean -C ..
	make clean -C swieta
.PHONY: clean
