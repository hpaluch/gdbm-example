CFLAGS = -g -Wall 
LDFLAGS = -g
LDLIBS = -lgdbm

all : gdbm_load gdbm_query
gdbm_load : gdbm_load.o
gdbm_load.o : gdbm_load.c

gdbm_query : gdbm_query.o
gdbm_query.o : gdbm_query.c

.PHONY: run
run: gdbm_load gdbm_query
	echo "Loading /usr/share/dict/wors into gdbm file..."
	./gdbm_load < /usr/share/dict/words && \
	echo "Running query program..." && \
	./gdbm_query

.PHONY: valgrind
valgrind: gdbm_load gdbm_query
	echo "Loading /usr/share/dict/wors into gdbm file..."
	valgrind ./gdbm_load < /usr/share/dict/words && \
	echo "Running query program..." && \
	valgrind ./gdbm_query


.PHONY: clean
clean:
	rm -f gdbm_load gdbm_query *.o *.gdbm

