# based on makefile by Adam Iwanicki
#
# ogolny makefile do kompilowania programow
# 2005.07.22 - modyfikacja parametrow kompilacji  (aiwanicki)
# 2009.12.05 - dodanie usuwania plikow .valgrind
# 2012.10.13 - opcja -U-FORTIFY_SOURCE
#

include ../makefile.in

CXXFLAGS = -std=c++11 -Wall -O2

PRG = $(wildcard *.cpp)

EXE = $(patsubst %.cpp,%.e,$(PRG))

all: $(EXE)

%.e: %.cpp
	g++ $(CXXFLAGS) $^ -o $*.e ${CXX_LDFLAGS}

clean:
	rm -f *.e
