CXXFLAGS += -O3 -W -Wall -std=c++11
#CXXFLAGS += -g -W -Wall -std=c++11

%.e: %.cpp
	g++ $(CXXFLAGS) $^ -o $*.e
