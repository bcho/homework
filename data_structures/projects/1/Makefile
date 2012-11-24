.PHONY: clean

CFLAGS=-g
CC=gcc

name=search

all: ${name}

${name}: list.o search.o time_measure.o main.o

clean:
	rm -f *.o
	rm -f ${name}

