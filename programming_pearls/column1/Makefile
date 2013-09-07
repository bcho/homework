.PHONY: clean

CFLAGS=-g

sort: sort.c bitvector.o usage.o

generate: generate.c bitvector.o

test: test_bitvector
	./test_bitvector

test_bitvector: test_bitvector.c bitvector.o

bitvector.o: bitvector.c

usage.o: usage.c

clean:
	rm -rf *.o test_bitvector generate sort
