ingen:
	python gen.py

clean:
	rm -f *.in *.out *.e

bin:
	make -B -C ..
	cp ../seed_lin.e .
	cp ../seed_nlogn.e .



.PHONY: ingen clean bin
