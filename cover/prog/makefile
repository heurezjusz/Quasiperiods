#
# ogolny makefile do kompilowania programow
# 2005.07.22 - modyfikacja parametrow kompilacji  (aiwanicki)
# 2009.12.05 - dodanie usuwania plikow .valgrind
# 2012.10.13 - opcja -U-FORTIFY_SOURCE
#

include ../makefile.in

CXXFLAGS=-std=c++11 -g

GCC_OPT = -Wall -lm -O2 -Wno-unused-result -Werror ${CFLAGS}
GPP_OPT = -Wall -lm -O2 -Wno-unused-result -Werror ${CXXFLAGS}
PPC_OPT = -O2 -XS -Xt -Ci -Cr -Co -gl ${PASFLAGS}

PRG_C 	= $(wildcard *.c)
PRG_CPP = $(wildcard *.cpp)
PRG_JAVA = $(wildcard *.java)
PRG_PAS = $(wildcard *.pas)
PRG_ML  = $(wildcard *.ml)
PRG     = $(PRG_C) $(PRG_CPP) $(PRG_PAS) $(PRG_ML)

EXE_C   = $(patsubst %.c,%.e,$(PRG_C))
EXE_CPP = $(patsubst %.cpp,%.e,$(PRG_CPP))
EXE_JAVA = $(patsubst %.java,%.e,$(PRG_JAVA))
EXE_PAS = $(patsubst %.pas,%.e,$(PRG_PAS))
EXE_ML  = $(patsubst %.ml,%.e,$(PRG_ML))
EXE     = $(EXE_C) $(EXE_CPP) $(EXE_JAVA) $(EXE_PAS) $(EXE_ML)

all: $(EXE) ${ID}.valgrind

%.e: %.pas
	fpc $(PPC_OPT) $*.pas ${PAS_LDFLAGS}
	mv $* $*.e

%.e: %.c
	gcc $(GCC_OPT) $^ -o $*.e ${C_LDFLAGS}

%.e: %.cpp
	g++ $(GPP_OPT) $^ -o $*.e ${CXX_LDFLAGS}

%.e: %.java
	javac $(JAVA_OPT) $^
	MEM=$$(($(MEMLIMIT) / 1000))M; \
	echo "ulimit -v unlimited ; java -client -Xmx$$MEM -Xms$$MEM -Xss$$MEM -cp \`dirname \$$0\` $*" > $*.e
	chmod 755 $*.e

%.e: %.ml
	ocamlopt $^ -o $*.e
	rm -f *.cmx
	rm -f *.cmi
	rm -f *.cmo

%.valgrind: %.c
	gcc -O2 ${CFLAGS} -g -lm $^ -o $*.valgrind ${C_LDFLAGS}

%.valgrind: %.cpp
	g++ -O2 ${CXXFLAGS} -g -lm $^ -o $*.valgrind ${CXX_LDFLAGS}

%.valgrind: %.pas %.e
	cp $*.e $*.valgrind

clean:
	rm -f *.o
	rm -f *.e
	rm -f *.valgrind
	rm -f *~
	rm -f *.class
	rm -f *.cmx
	rm -f *.cmi
	rm -f *.cmo

-include makefile.user
