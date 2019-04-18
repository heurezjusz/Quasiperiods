include ../makefile.inc
DEP = $(wildcard ../*.cpp ../*.h)

make_sup: $(DEP)
	make -C ..
.PHONY: make_sup


clean:
	rm -f *.o
	rm -f *.e
	make clean -C ..
.PHONY: clean 


# target: partitions

partitions: partitions.e partitions_rand_labels.e partitions_slow.e partitions_rand_renames.e
.PHONY: partitions

partitions.e: partitions_test.cpp make_sup
	g++ partitions_test.cpp $(CXXFLAGS) ../partition.o -o $@

partitions_rand_labels.e: partitions_test_rand_labels.cpp make_sup
	g++ partitions_test_rand_labels.cpp $(CXXFLAGS) ../partition.o -o $@

partitions_rand_renames.e: partitions_test_rand_renames.cpp make_sup
	g++ partitions_test_rand_renames.cpp $(CXXFLAGS) ../partition.o -o $@

partitions_slow.e: partitions_slow.cpp
	g++ partitions_slow.cpp $(CXXFLAGS) -o $@


# target: hull
hull: hull.e hull_slow.e
.PHONY: hull

hull.e: make_sup
	g++ hull.cpp ../hull.o $(CXXFLAGS) $(LDFLAGS) -o $@

hull_slow.e:
	g++ hull_slow.cpp $(CXXFLAGS) -o $@
