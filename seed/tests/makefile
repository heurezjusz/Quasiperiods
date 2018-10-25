include ../makefile.inc
CXXFLAGS += -g
DEP = $(wildcard ../*.cpp ../*.h)

make_sup: $(DEP)
	make -C ..
.PHONY: make_sup


# target: combine

combine: combine.e combine_slow.e packs_chk.e
.PHONY: combine

combine_slow.o: combine_slow.cpp ../combine.h
	g++ combine_slow.cpp $(CXXFLAGS) -c -o $@

combine.o: combine.cpp ../combine.h
	g++ combine.cpp $(CXXFLAGS) -c -o $@

combine.e: combine.o make_sup
	g++ combine.o ../ukkonen.o ../combine.o -o $@ $(LFLAGS)


# target: maxgap
maxgap: maxgap_slow.e maxgap.e
.PHONY: maxgap

maxgap_slow.e: maxgap_slow.cpp ../pack.h
	g++ maxgap_slow.cpp $(CXXFLAGS) -o $@

maxgap.o: maxgap.cpp
	g++ maxgap.cpp -std=c++11 -W -Wall -c -o $@

maxgap.e: maxgap.o make_sup
	g++ maxgap.o ../maxgap.o ../pack.o -o $@ $(LFLAGS)


# target: maxgap_nlogn
maxgap_nlogn: maxgap_nlogn_slow.e maxgap_nlogn.e
.PHONY: maxgap_nlogn

maxgap_nlogn_slow.e: maxgap_nlogn_slow.cpp
	g++ maxgap_nlogn_slow.cpp $(CXXFLAGS) -o $@

maxgap_nlogn.o: maxgap_nlogn.cpp
	g++ maxgap_nlogn.cpp -std=c++11 -W -Wall -c -o $@

maxgap_nlogn.e: maxgap_nlogn.o make_sup
	g++ maxgap_nlogn.o ../maxgap_nlogn.o -o $@ $(LFLAGS)


# target: ukkonen
ukkonen: ukkonen.e
.PHONY: ukkonen

ukkonen.o: ukkonen.cpp
	g++ ukkonen.cpp $(CXXFLAGS) -c -o $@
ukkonen.e: ukkonen.o make_sup
	g++ ukkonen.o ../ukkonen.o -o $@ $(LFLAGS)


# target: ukkonen_perf
ukkonen_perf: ukkonen_perf.e ukkonen_perf_slow.e
.PHONY: ukkonen_perf

ukkonen_perf.o: ukkonen_perf.cpp
	g++ ukkonen_perf.cpp $(CXXFLAGS) -c -o $@

ukkonen_perf.e: ukkonen_perf.o make_sup
	g++ ukkonen_perf.o ../ukkonen.o -o $@ $(LFLAGS)

ukkonen_perf_slow.o: ukkonen_perf_slow.cpp
	g++ ukkonen_perf_slow.cpp $(CXXFLAGS) -c -o $@

ukkonen_perf_slow.e: ukkonen_perf_slow.o make_sup
	g++ ukkonen_perf_slow.o ../ukkonen.o -o $@ $(LFLAGS)


# target: lcands
lcands: lcands.e packs_chk.e
.PHONY: lcands

lcands.e: make_sup lcands.o
	g++ lcands.o ../lcands.o -o $@ $(LFLAGS)


# target: rmcands
rmcands: rmcands.e rmcands_chk.e
.PHONY: rmcands

rmcands_chk.e: rmcands_chk.cpp
	g++ rmcands_chk.cpp -o $@ $(CXXFLAGS)

rmcands.e: make_sup rmcands.o
	g++ rmcands.o ../rmcands.o ../ukkonen.o ../pack.o ../maxgap.o -o $@ $(LFLAGS)


# target: rmcands_nlogn
rmcands_nlogn: rmcands_nlogn.e rmcands_chk.e
.PHONY: rmcands_nlogn

rmcands_nlogn.e: make_sup rmcands_nlogn.o
	g++ rmcands_nlogn.o ../rmcands_nlogn.o ../ukkonen.o ../pack.o ../maxgap_nlogn.o -o $@ $(LFLAGS)


#target: seeds nlogn
seeds_nlogn: packs_chk.e make_sup
	cp ../main_nlogn.e seeds_nlogn.e
.PHONY: seeds_nlogn


%.e: %.o
	g++ $^ -o $@ $(LFLAGS)

clean:
	rm -f *.o
	rm -f *.e
	make clean -C ..
.PHONY: clean 
