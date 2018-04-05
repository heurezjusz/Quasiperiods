include ../makefile.inc

# target: combine

combine: combine.e combine_slow.e combine_chk.e

COMBINE_DEP = ../combine/combine.o ../ukkonen/ukkonen.o

combine_slow.o: combine_slow.cpp ../combine/combine.hpp
	g++ combine_slow.cpp $(CXXFLAGS) -c -o $@

combine.o: combine.cpp ../combine/combine.hpp
	g++ combine.cpp $(CXXFLAGS) -c -o $@

combine.e: combine.o $(COMBINE_DEP)
	g++ combine.o $(COMBINE_DEP) -o $@ $(LFLAGS)


# target: maxgap
maxgap: maxgap_slow.e maxgap.e

structs:
	make -C ../structs

MAXGAP_O = ../structs/structs.o
STRUCT_DEP = ../structs/structs.hpp ../structs/structs.cpp structs

maxgap_slow.e: maxgap_slow.cpp ../structs/structs.hpp
	g++ maxgap_slow.cpp $(CXXFLAGS) -o $@

maxgap.o: maxgap.cpp
	g++ maxgap.cpp -std=c++11 -W -Wall -c -o $@

maxgap.e: maxgap.o $(MAXGAP_O) $(STRUCT_DEP)
	g++ maxgap.o $(MAXGAP_O) -o $@ $(LFLAGS)


# target: ukkonen
ukkonen: ukkonen.e
ukkonen_o:
	make -C ../ukkonen

ukkonen.o: ukkonen.cpp
	g++ ukkonen.cpp $(CXXFLAGS) -c -o $@
ukkonen.e: ukkonen.o ../ukkonen/ukkonen.hpp ../ukkonen/ukkonen.cpp ukkonen_o
	g++ ukkonen.o ../ukkonen/ukkonen.o -o $@ $(LFLAGS)


ukkonen_perf: ukkonen_perf.e ukkonen_perf_slow.e

ukkonen_perf.o: ukkonen_perf.cpp
	g++ ukkonen_perf.cpp $(CXXFLAGS) -c -o $@
ukkonen_perf.e: ukkonen_perf.o ../ukkonen/ukkonen.hpp ../ukkonen/ukkonen.cpp ukkonen_o
	g++ ukkonen_perf.o ../ukkonen/ukkonen.o -o $@ $(LFLAGS)

ukkonen_perf_slow.o: ukkonen_perf_slow.cpp
	g++ ukkonen_perf_slow.cpp $(CXXFLAGS) -c -o $@
ukkonen_perf_slow.e: ukkonen_perf_slow.o ../ukkonen/ukkonen.hpp ../ukkonen/ukkonen.cpp ukkonen_o
	g++ ukkonen_perf_slow.o ../ukkonen/ukkonen.o -o $@ $(LFLAGS)


%.e: %.o
	g++ $^ -o $@ $(LFLAGS)

clean:
	rm -f *.o
	rm -f *.e

.PHONY: clean combine maxgap structs ukkonen ukkonen_perf
