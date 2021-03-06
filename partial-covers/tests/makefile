include ../lib/src/makefile.inc
DEP = $(wildcard ../lib/src/*.cpp ../lib/src/*.h)

make_sup: $(DEP)
	make -C ../lib/
	make -C ../bin/
.PHONY: make_sup


clean:
	rm -f *.o
	rm -f *.e
	make clean -C ../lib/src
.PHONY: clean


# target: partitions

partitions: partitions.e partitions_rand_labels.e partitions_slow.e partitions_rand_renames.e
.PHONY: partitions

partitions.e: partitions_test.cpp make_sup
	g++ partitions_test.cpp $(CXXFLAGS) ../lib/src/partition.o -o $@

partitions_rand_labels.e: partitions_test_rand_labels.cpp make_sup
	g++ partitions_test_rand_labels.cpp $(CXXFLAGS) ../lib/src/partition.o -o $@

partitions_rand_renames.e: partitions_test_rand_renames.cpp make_sup
	g++ partitions_test_rand_renames.cpp $(CXXFLAGS) ../lib/src/partition.o -o $@

partitions_slow.e: partitions_slow.cpp
	g++ partitions_slow.cpp $(CXXFLAGS) -o $@


# target: hull
hull: hull.e hull_slow.e
.PHONY: hull

hull.e: make_sup
	g++ hull.cpp ../lib/src/hull.o $(CXXFLAGS) $(LDFLAGS) -o $@

hull_slow.e:
	g++ hull_slow.cpp $(CXXFLAGS) -o $@


# target: ukkonen
ukkonen: ukkonen.e
.PHONY: ukkonen

ukkonen.e: ukkonen.cpp make_sup
	g++ ukkonen.cpp ../lib/src/ukkonen.o $(CXXFLAGS) $(LDFLAGS) -o $@

# target: ukkonen_depth
ukkonen_depth: ukkonen_depth.e
.PHONY: ukkonen_depth

ukkonen_depth.e: ukkonen_depth.cpp make_sup
	g++ ukkonen_depth.cpp ../lib/src/ukkonen.o $(CXXFLAGS) $(LDFLAGS) -o $@


# target: cst
cst: cst.e
.PHONY: cst

cst.e: cst.cpp make_sup
	g++ cst.cpp ../lib/src/ukkonen.o ../lib/src/cst.o ../lib/src/partition.o $(CXXFLAGS) $(LDFLAGS) -o $@


# target: cst_vals
cst_vals: cst_vals.e
.PHONY: cst_vals

cst_vals.e: cst_vals.cpp make_sup
	g++ cst_vals.cpp ../lib/src/ukkonen.o ../lib/src/cst.o ../lib/src/partition.o $(CXXFLAGS) $(LDFLAGS) -o $@


# target: algorithm_all
algorithm_all: algorithm_all.e algorithm_all_slow.e
.PHONY: algorithm_all

algorithm_all_slow.e: make_sup
	make -C ../lib/src slow_algorithm.e
	cp ../lib/src/slow_algorithm.e $@

algorithm_all.e: make_sup
	cp ../bin/partial_covers_all.e $@


# target: algorithm_single
algorithm_single: algorithm_single.e algorithm_single_slow.e
.PHONY: algorithm_single

algorithm_single_slow.e: make_sup
	make -C ../lib/src slow_algorithm_single.e
	cp ../lib/src/slow_algorithm_single.e $@

algorithm_single.e: make_sup
	cp ../bin/partial_covers_single.e $@
