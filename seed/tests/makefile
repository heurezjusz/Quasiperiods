include ../makefile.inc

# target: combine

combine: combine.e combine_slow.e combine_chk.e

COMBINE_DEP = ../combine.o ../ukkonen.o

combine_slow.o: combine_slow.cpp ../combine.h
	g++ combine_slow.cpp $(CXXFLAGS) -c -o $@

combine.o: combine.cpp ../combine.h
	g++ combine.cpp $(CXXFLAGS) -c -o $@

combine.e: combine.o $(COMBINE_DEP)
	g++ combine.o $(COMBINE_DEP) -o $@ $(LFLAGS)


# target: maxgap
maxgap: maxgap_slow.e maxgap.e
.PHONY: maxgap

../lin/maxgap.o:
	make -C ../lin

MAXGAP_O = ../lin/maxgap.o

maxgap_slow.e: maxgap_slow.cpp ../pack.h
	g++ maxgap_slow.cpp $(CXXFLAGS) -o $@

maxgap.o: maxgap.cpp
	g++ maxgap.cpp -std=c++11 -W -Wall -c -o $@

maxgap.e: maxgap.o $(MAXGAP_O) ../pack.o
	g++ maxgap.o $(MAXGAP_O) ../pack.o -o $@ $(LFLAGS)


# target: maxgap_nlogn
maxgap_nlogn: maxgap_nlogn_slow.e maxgap_nlogn.e

../nlogn/maxgap.o: ../nlogn/maxgap.cpp ../nlogn/maxgap.h
	make -C ../nlogn

maxgap_nlogn_slow.e: maxgap_nlogn_slow.cpp
	g++ maxgap_nlogn_slow.cpp $(CXXFLAGS) -o $@

maxgap_nlogn.o: maxgap_nlogn.cpp
	g++ maxgap_nlogn.cpp -std=c++11 -W -Wall -c -o $@

maxgap_nlogn.e: maxgap_nlogn.o ../nlogn/maxgap.o ../nlogn/maxgap.cpp ../nlogn/maxgap.h
	g++ maxgap_nlogn.o ../nlogn/maxgap.o -o $@ $(LFLAGS)

.PHONY: maxgap_nlogn

# target: ukkonen
ukkonen: ukkonen.e
ukkonen_o:
	make -C .. ukkonen.o

ukkonen.o: ukkonen.cpp
	g++ ukkonen.cpp $(CXXFLAGS) -c -o $@
ukkonen.e: ukkonen.o ../ukkonen.h ../ukkonen.cpp ukkonen_o
	g++ ukkonen.o ../ukkonen.o -o $@ $(LFLAGS)


ukkonen_perf: ukkonen_perf.e ukkonen_perf_slow.e

ukkonen_perf.o: ukkonen_perf.cpp
	g++ ukkonen_perf.cpp $(CXXFLAGS) -c -o $@
ukkonen_perf.e: ukkonen_perf.o ../ukkonen.h ../ukkonen.cpp ukkonen_o
	g++ ukkonen_perf.o ../ukkonen.o -o $@ $(LFLAGS)

ukkonen_perf_slow.o: ukkonen_perf_slow.cpp
	g++ ukkonen_perf_slow.cpp $(CXXFLAGS) -c -o $@
ukkonen_perf_slow.e: ukkonen_perf_slow.o ../ukkonen.h ../ukkonen.cpp ukkonen_o
	g++ ukkonen_perf_slow.o ../ukkonen.o -o $@ $(LFLAGS)


# target: lcands
lcands: lcands.e combine_chk.e

lcands.e: ../lcands.cpp ../lcands.h lcands.o
	make -C .. lcands.o
	g++ lcands.o ../lcands.o -o $@ $(LFLAGS)

# target: rmcands
rmcands: rmcands.e rmcands_chk.e

rmcands_chk.e: rmcands_chk.cpp
	g++ rmcands_chk.cpp -o $@ $(CXXFLAGS)

rmcands.e: ../rmcands.o ../maxgap.o ../pack.o ../ukkonen.o rmcands.o
	make -C .. rmcands.o
	g++ rmcands.o ../rmcands.o ../ukkonen.o ../pack.o ../maxgap.o -o $@ $(LFLAGS)



%.e: %.o
	g++ $^ -o $@ $(LFLAGS)

clean:
	rm -f *.o
	rm -f *.e

.PHONY: clean combine maxgap structs ukkonen ukkonen_perf lcands rmcands
