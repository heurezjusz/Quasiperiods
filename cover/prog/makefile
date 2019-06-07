CXXFLAGS = -std=c++11 -Wall -O2

PRG = $(wildcard *.cpp)

EXE = $(patsubst %.cpp,%.e,$(PRG))

all: $(EXE)

%.e: %.cpp
	g++ $(CXXFLAGS) $^ -o $*.e ${CXX_LDFLAGS}

clean:
	rm -f *.e
