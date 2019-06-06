all: prog compile

prog:
	make -C ../seed
	cp ../seed/seed_lin.e prog/seed_kociumaka.e
	cp ../seed/seed_nlogn.e prog/seed_kociumaka_nlogn.e
	cp ../seed/seed_imp.e prog/

.PHONY: prog


clean:
	rm prog/*.e -f
	make clean -C swieta
	make clean -C big_seeds
	make clean -C letters
	make clean -C per_seed_big
	make clean -C periodic
	make clean -C small_seeds
	make clean -C big_periods
	make clean -C little_periods
	make clean -C per_seed_small
	make clean -C random
	make clean -C small_periods
.PHONY: clean


clean-gen:
	make clean-gen -C big_seeds
	make clean-gen -C letters
	make clean-gen -C per_seed_big
	make clean-gen -C periodic
	make clean-gen -C small_seeds
	make clean-gen -C big_periods
	make clean-gen -C little_periods
	make clean-gen -C per_seed_small
	make clean-gen -C random
	make clean-gen -C small_periods
.PHONY: clean-gen
