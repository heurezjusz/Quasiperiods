include ../makefile.inc

default: main

main: main.cpp maxgap.o
	g++ $(CXXFLAGS) main.cpp maxgap.o $(LNFLAGS) -o main

clean:
	rm main *.o -f

.PHONY: default clean
