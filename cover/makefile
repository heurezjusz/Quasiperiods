# based on makefile by Tomasz Walen, Rafal Rusin, Adam Iwanicki
# written for Polish Olympiad in Informatics 

SHELL := /bin/bash

include makefile.in

BIN_TIME = /usr/bin/time
TMP1     = .__tmp_1__~
TMP2     = .__tmp_2__~
TMP3     = .__tmp_3__~
TMP4     = .__tmp_4__~

CHECKER = $(shell if [ `find prog -name "$(ID)chk.*" | wc -l` -gt 0 ] ; then echo 1 ; else echo 0 ; fi)

PROGS_OPT = $(shell find prog -regex "prog/$(ID)\([0-9]*\|_.*\)\.\(c\|cpp\|pas\|ml\)" | sort -n -k 1.`echo "prog/$(ID)"| wc -c`)

TESTS = $(shell find -L in -regex "in/$(ID)[0-9]*[a-z]?.in" | sort -n -k 1.`echo "in/$(ID)"| wc -c` )


.PHONY : clean run outgen


all:
	# specify target: outgen / run_all / run_XXX / clean #


run_all:
	make run_afi
	make run_breslauer
	make run_folk
	make run_ms
	make run_ms_static_mem


run%:  
	make -C prog
	make _run_ver_n_$(ID)$*.e


clean:
	rm -f *~
	make -C prog clean


outgen:
	make -C prog $(ID).e
	@for i in $(TESTS) ; do \
	    printf "%-11s ... " `basename $$i` ; \
	    prog/$(ID).e < $$i > out/`basename $$i .in`.out ; \
	    echo OK ; \
	done 


_run_ver_n_%:
	make -s -C prog $*
	@if [ "$(CHECKER)" -eq "1" ] ; then make -C prog $(ID)chk.e ; fi
	@ACC_TERM=0;\
	STOP_ON_WRONG=1;\
	T_LIMIT=$(TIMELIMIT);\
	RT_LIMIT=$$(($(TIMELIMIT) * 10 + 100)); \
	PID='';\
	function sig_handler() { \
		if [ -n "$$PID" ]; then \
			kill -SIGKILL -$$PID >/dev/null 2>&1; \
			wait $$PID >/dev/null 2>&1; \
		fi; \
	}; \
	trap sig_handler SIGINT ; \
	for i in $(TESTS) ; do \
		j=out/`basename $$i .in`.out ; \
		\
		printf "%-11s " `basename $$i` ; \
		\
		rm -f $(TMP3);\
		rm -f $(TMP1);\
		setsid bash -c "ulimit -v $(MEMLIMIT); ulimit -t $$T_LIMIT ; \
				$(BIN_TIME) -f \"%U\" -o $(TMP2) prog/$* <$$i >$(TMP1)" >/dev/null 2>&1 & \
		PID=$$!; \
		setsid bash -c "sleep $$RT_LIMIT && kill -SIGKILL -$$PID" >/dev/null 2>&1 & \
		S_PID=$$!; \
		while ! kill -0 -$$S_PID >/dev/null 2>&1; do true; done; \
		wait $$PID >/dev/null 2>&1; \
		if [ "0" -eq "$$?" ]; then echo "OK" >$(TMP3); else echo "STOPPED" >$(TMP3); fi; \
		if [ "`cat $(TMP3)`" = OK ]; then TERM=0; else TERM=1; fi;\
		rm -f $(TMP3);\
		kill -SIGKILL -$$S_PID >/dev/null 2>&1; \
		if [ "0" -eq "$$?" ]; then TIMEOUT=0; else TIMEOUT=1; TERM=1; echo "$$RT_LIMIT.00" > $(TMP2); fi;\
		wait $$S_PID >/dev/null 2>&1; \
		TIME=`cat $(TMP2)` ; echo -n "$$TIME " ; \
		\
		if [ $$TERM -eq 0 ]; then \
			if [ "$(CHECKER)" -eq "1" ] ; then \
				prog/$(ID)chk.e $$i $(TMP1) $$j > $(TMP2) ; \
				RES=`head -n 1 $(TMP2)` ; \
				COMMENT=`head -n 2 $(TMP2) | tail -n 1` ; \
				if [ "$$RES" != "OK" ] ; then RES="WRONG_ANSWER" ; fi ; \
			else \
				if diff -q $$j $(TMP1) > /dev/null ; then \
					RES="OK" ; \
				else \
					RES="WRONG_ANSWER" ; \
				fi ; \
				COMMENT="" ; \
			fi ; \
		fi; \
		if [ $$TERM -eq 1 ]; then RES="WRONG (TIMEOUT)"; fi; \
		if [ $$TERM -eq 1 ] && [ "$$ACC_TERM" = 1 ]; then RES="OK"; fi; \
		if [ $$TIMEOUT -eq 1 ]; then RES="\x1b[31m!REAL TIMEOUT!\x1b[0m"; fi; \
		printf "$$RES $$COMMENT\n" ; \
		rm -f $(TMP1) $(TMP2) ; \
		if [ "$$RES" != "OK" ] && [ "$$STOP_ON_WRONG" = 1 ]; then exit 1; fi;\
	done
