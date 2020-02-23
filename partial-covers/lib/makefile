include ../makefile.inc


OBJS = partition.o
OBJS_ALL = $(OBJS) algorithm_all.o hull.o ukkonen.o cst.o
OBJS_SINGLE = $(OBJS) algorithm_single.o ukkonen_leafs.o cst_leafs.o

DIRS = algorithm_all algorithm_single

all: $(DIRS)

algorithm_all:
	make -C src
	mkdir $@
	for obj in $(OBJS_ALL) ; do \
		ln -s ../src/$$obj $@/$$obj ; \
	done

algorithm_single:
	make -C src
	mkdir $@
	for obj in $(OBJS_SINGLE) ; do \
		ln -s ../src/$$obj $@/$$obj ; \
	done

clean:
	make clean -C src
	rm -rf $(DIRS)

.PHONY: clean