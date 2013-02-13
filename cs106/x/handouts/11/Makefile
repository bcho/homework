CCFLAGS=-g

.PHONY: clean

p1: p1.c map.o pair.o str.o

keith-numbers: keith-numbers.c

test: str_test
	./str_test

str_test: str.o str_test.c

clean:
	rm -f *.o
	rm -f *_test
	rm -f p1
	rm -f keith-numbers
