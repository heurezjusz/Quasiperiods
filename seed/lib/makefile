include ../makefile.inc

OBJS = combine.o pack.o ukkonen.o lcands.o
OBJS_N = maxgap.o rmcands.o rmcands_lens.o rmcands_16.o algorithm.o $(OBJS)
OBJS_NLOGN = maxgap_nlogn.o rmcands_nlogn.o algorithm_nlogn.o $(OBJS)

OBJS_IMP = pack.o maxgap_imp.o algorithm_imp.o
OBJS_IMP_SLOW = pack.o maxgap_imp_nlogn.o algorithm_imp_slow.o

DIRS_DEV = kkrrw kkrrws imp
DIRS = $(DIRS_DEV) imp_slow


all: $(DIRS_DEV)


kkrrw:
	make -C src
	mkdir $@
	for obj in $(OBJS_N) ; do \
		ln -s ../src/$$obj $@/$$obj ; \
	done

kkrrws:
	make -C src
	mkdir $@
	for obj in $(OBJS_NLOGN) ; do \
		ln -s ../src/$$obj $@/$$obj ; \
	done

imp:
	make -C src
	mkdir $@
	for obj in $(OBJS_IMP) ; do \
		ln -s ../src/$$obj $@/$$obj ; \
	done

imp_slow:
	make -C src
	mkdir $@
	for obj in $(OBJS_IMP_SLOW) ; do \
		ln -s ../src/$$obj $@/$$obj ; \
	done


clean:
	make clean -C src
	rm -rf $(DIRS)

.PHONY: clean