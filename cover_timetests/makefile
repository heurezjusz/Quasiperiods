all: prog compile

prog:
	cp ../cover/prog/cover_*.cpp prog/
	cp ../cover/prog/maxN.h prog/

.PHONY: prog


compile:
	make -C prog
.PHONY: compile


clean:
	make -C prog clean
	make -C random clean
.PHONY: clean


run_random:
	python3 run.py random
.PHONY: run_random


report_%.txt: run_%

plot_%: report_%.txt
	python3 plot_summary.py %