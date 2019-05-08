CXXFLAGS += -O3 -W -Wall -std=c++11

all: prog compile


prog:
	cp ../cover/prog/cover_*.cpp .

.PHONY: prog

PRG_CPP = $(wildcard cover_*.cpp)
EXE_CPP = $(patsubst %.cpp,%.e,$(PRG_CPP))

compile: $(EXE_CPP)
.PHONY: compile

%.e: %.cpp
	g++ $(CXXFLAGS) $^ -o $*.e
