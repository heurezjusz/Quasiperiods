include makefile.inc

tree.o: tree.cpp
	g++ tree.cpp $(CXXFLAGS) -c -o tree.o

%.e: %.o
	g++ $^ -o $@ $(LFLAGS)

clean:
	make clean -C combine
	make clean -C tests
