include ../makefile.inc

# target: combine

combine: combine_str.e combine_slow.e combine_chk.e

COMBINE_O = ../combine/combine.o

combine_slow.o: combine_slow.cpp ../combine/combine.hpp
	g++ combine_slow.cpp $(CXXFLAGS) -c -o $@

combine_str.o: combine_str.cpp ../combine/combine.hpp
	g++ combine_str.cpp $(CXXFLAGS) -c -o $@

combine_str.e: combine_str.o $(COMBINE_O)
	g++ combine_str.o $(COMBINE_O) -o $@ $(LFLAGS)

# combine_tree.o: combine_tree.cpp ../combine/combine.hpp
# 	g++ combine_tree.cpp $(CXXFLAGS) -c -o $@

combine_tree.e: combine_tree.o $(COMBINE_O)
	g++ combine_tree.o $(COMBINE_O) -o $@ $(LFLAGS)


# target: maxgap
maxgap: maxgap_slow.e maxgap.e

structs:
	make -C ../structs
utils:
	make -C ../utils

MAXGAP_O = ../structs/structs.o
STRUCT_DEP = ../structs/structs.hpp ../structs/structs.cpp structs
UTILS_DEP = ../utils/utils.hpp ../utils/utils.cpp utils


maxgap_slow.e: maxgap_slow.cpp ../structs/structs.hpp
	g++ maxgap_slow.cpp $(CXXFLAGS) -o $@

maxgap.o: maxgap.cpp
	g++ maxgap.cpp -std=c++11 -W -Wall -c -o $@

maxgap.e: maxgap.o $(MAXGAP_O) $(STRUCT_DEP)
	g++ maxgap.o $(MAXGAP_O) -o $@ $(LFLAGS)


# target: depths
depths: depths_slow.e depths.e

depths_slow.e: depths_slow.cpp
	g++ depths_slow.cpp $(CXXFLAGS) -o $@ $(LFLAGS)

depths.o: depths.cpp
	g++ depths.cpp $(CXXFLAGS) -c -o $@

depths.e: depths.o $(UTILS_DEP)
	g++ depths.o ../utils/utils.o -o $@ $(LFLAGS)

%.e: %.o
	g++ $^ -o $@ $(LFLAGS)

clean:
	rm -f *.o
	rm -f *.e

.PHONY: clean combine maxgap structs depths
