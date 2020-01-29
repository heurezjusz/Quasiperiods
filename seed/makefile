include makefile.inc


seed_lin.e: bin/main.o lib/kkrrw
	g++ bin/main.o $(wildcard lib/kkrrw/*) -o $@ $(LFLAGS)

# seed_nlogn.e: main.o $(OBJS_NLOGN) $(HEADERS)
# 	g++ $(OBJS_NLOGN) main.o -o $@ $(LFLAGS)

# seed_imp_slow.e: main.o $(OBJS_COSTAS_SLOW) $(HEADERS)
# 	g++ $(OBJS_COSTAS_SLOW) main.o -o $@ $(LFLAGS)

# seed_imp.e: main.o $(OBJS_COSTAS) $(HEADERS)
# 	g++ $(OBJS_COSTAS) main.o -o $@ $(LFLAGS)


# seed_imp_int.e: main_int.o $(OBJS_COSTAS) $(HEADERS)
# 	g++ $(OBJS_COSTAS) main_int.o -o $@ $(LFLAGS)

# seed_imp_slow_int.e: main_int.o $(OBJS_COSTAS_SLOW) $(HEADERS)
# 	g++ $(OBJS_COSTAS_SLOW) main_int.o -o $@ $(LFLAGS)

# seed_nlogn_int.e: main_int.o $(OBJS_NLOGN) $(HEADERS)
# 	g++ $(OBJS_NLOGN) main_int.o -o $@ $(LFLAGS)

# seed_lin_int.e: main_int.o $(OBJS_N) $(HEADERS)
# 	g++ $(OBJS_N) main_int.o -o $@ $(LFLAGS)


lib/%:
	make -C lib $(patsubst lib/%,%,$@)

clean:
	make clean -C bin
	make clean -C lib
	rm *.e

.PHONY: clean all
