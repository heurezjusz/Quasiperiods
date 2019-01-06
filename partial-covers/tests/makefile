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


# target: combine

partitions: patritions.e partitions_rand_labels.e partitions_slow.e partitions_rand_renames.e
.PHONY: partitions

partitions.e: partitions_test.cpp make_sup
	g++ partitions_test.cpp $(CXXFLAGS) ../partitions.o -o $@

partitions_rand_labels.e: partitions_test_rand_labels.cpp make_sup
	g++ partitions_test_rand_labels.cpp $(CXXFLAGS) ../partitions.o -o $@

partitions_rand_renames.e: partitions_test_rand_renames.cpp make_sup
	g++ partitions_test_rand_renames.cpp $(CXXFLAGS) ../partitions.o -o $@

partitions_slow.e: partitions_slow.cpp
	g++ partitions_slow.cpp $(CXXFLAGS) -o $@

