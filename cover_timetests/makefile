all: prog compile

prog:
	cp ../cover/prog/cover_*.cpp prog/
	cp ../cover/prog/maxN.h prog/

.PHONY: prog


compile:
	make -C prog
.PHONY: compile


clean:
	make clean -C prog
	make clean -C swieta
	make clean -C big_covers
	make clean -C letters
	make clean -C per_cover_big    
	make clean -C periodic
	make clean -C recursive
	make clean -C small_covers
	make clean -C big_periods
	make clean -C little_periods
	make clean -C per_cover_small
	make clean -C random
	make clean -C small_periods
.PHONY: clean


clean-gen:
	make clean-gen -C big_covers
	make clean-gen -C letters
	make clean-gen -C per_cover_big    
	make clean-gen -C periodic
	make clean-gen -C recursive
	make clean-gen -C small_covers
	make clean-gen -C big_periods
	make clean-gen -C little_periods
	make clean-gen -C per_cover_small
	make clean-gen -C random
	make clean-gen -C small_periods
.PHONY: clean-gen
