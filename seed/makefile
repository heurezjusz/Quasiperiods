include makefile.inc

all: seed_lin.e seed_nlogn.e seed_costas_slow.e seed_costas.e seed_lin_int.e seed_nlogn_int.e seed_costas_int.e seed_costas_slow_int.e

OBJS = combine.o pack.o ukkonen.o lcands.o
OBJS_N = maxgap.o rmcands.o rmcands_lens.o rmcands_16.o algorithm.o $(OBJS)
OBJS_NLOGN = maxgap_nlogn.o rmcands_nlogn.o algorithm_nlogn.o $(OBJS)

OBJS_COSTAS = pack.o maxgap_costas.o algorithm_costas.o
OBJS_COSTAS_SLOW = pack.o maxgap_costas_nlogn.o algorithm_costas_slow.o

HEADERS = $(wildcard *.h)


rmcands_lens.o: rmcands.cpp rmcands_lens.h
	g++ $< $(CXXFLAGS) -DLENS -c -o $@

rmcands_16.o: rmcands.cpp rmcands16.h
	g++ $< $(CXXFLAGS) -DMX16 -c -o $@

maxgap_costas_nlogn.o: maxgap_costas_nlogn.cpp maxgap_costas.h
	g++ $< $(CXXFLAGS) -c -o $@

maxgap_costas.o: maxgap_costas.cpp maxgap_costas.h
	g++ $< $(CXXFLAGS) -c -o $@


main.o: main.cpp
	g++ $< $(CXXFLAGS) -c -o $@

main_int.o: main_int.cpp
	g++ $< $(CXXFLAGS) -c -o $@


algorithm_nlogn.o: algorithm_nlogn.cpp algorithm.h
	g++ $< $(CXXFLAGS) -c -o $@

algorithm_costas.o: algorithm_costas.cpp algorithm.h
	g++ $< $(CXXFLAGS) -c -o $@

algorithm_costas_slow.o: algorithm_costas.cpp algorithm.h
	g++ $< $(CXXFLAGS) -DMXGAP_NLOGN -c -o $@


%.o: %.cpp %.h
	g++ $< $(CXXFLAGS) -c -o $@


seed_lin.e: main.o $(OBJS_N) $(HEADERS)
	g++ $(OBJS_N) main.o -o $@ $(LFLAGS)

seed_nlogn.e: main.o $(OBJS_NLOGN) $(HEADERS)
	g++ $(OBJS_NLOGN) main.o -o $@ $(LFLAGS)

seed_costas_slow.e: main.o $(OBJS_COSTAS_SLOW) $(HEADERS)
	g++ $(OBJS_COSTAS_SLOW) main.o -o $@ $(LFLAGS)

seed_costas.e: main.o $(OBJS_COSTAS) $(HEADERS)
	g++ $(OBJS_COSTAS) main.o -o $@ $(LFLAGS)


seed_costas_int.e: main_int.o $(OBJS_COSTAS) $(HEADERS)
	g++ $(OBJS_COSTAS) main_int.o -o $@ $(LFLAGS)

seed_costas_slow_int.e: main_int.o $(OBJS_COSTAS_SLOW) $(HEADERS)
	g++ $(OBJS_COSTAS_SLOW) main_int.o -o $@ $(LFLAGS)

seed_nlogn_int.e: main_int.o $(OBJS_NLOGN) $(HEADERS)
	g++ $(OBJS_NLOGN) main_int.o -o $@ $(LFLAGS)

seed_lin_int.e: main_int.o $(OBJS_N) $(HEADERS)
	g++ $(OBJS_N) main_int.o -o $@ $(LFLAGS)


clean:
	rm -rf *.o *.e


.PHONY: clean all
