all: prog compile

prog:
	make -C ../seed
	cp ../seed/seed_lin.e prog/seed_kociumaka.e
	cp ../seed/seed_nlogn.e prog/seed_kociumaka_nlogn.e
	cp ../seed/seed_costas.e prog/

.PHONY: prog


clean:
	make -C prog clean
	echo "=== *** +++ run clean in subfolders! +++ *** ==="
.PHONY: clean


run_random:
	python3 run.py random
.PHONY: run_random


report_%.txt: run_%
