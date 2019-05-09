include ../makefile.inc

PRG_CPP = $(wildcard *.cpp)
EXE_CPP = $(patsubst %.cpp,%.e,$(PRG_CPP))

all: $(EXE_CPP)

clean:
	rm -f *.e

.PHONY: all clean