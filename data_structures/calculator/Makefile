.PHONY: clean

CFLAGS=-g
CC=gcc

name=calculator

all: ${name}

${name}: ${name}.o convert.o tree.o main.o

clean:
	rm -f *.o
	rm -f ${name}

