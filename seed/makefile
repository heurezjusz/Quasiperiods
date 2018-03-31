CXXFLAGS = -DNDEBUG -O3 -std=c++11 -I /usr/local/include -L /usr/local/lib
LFLAGS =  -lsdsl -ldivsufsort -ldivsufsort64

tree.o: tree.cpp
	g++ tree.cpp $(CXXFLAGS) -c -o tree.o

%.e: %.o
	g++ $^ -o $@ $(LFLAGS)

clean:
	make clean -C combine