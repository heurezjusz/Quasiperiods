all: prog compile

prog:
	cp ../cover/prog/cover_*.cpp prog/

.PHONY: prog


compile:
	make -C prog
.PHONY: compile


clean:
	make -C prog clean
	make -C random clean
.PHONY: clean
