.PHONY: clean

CFLAGS=-g
CC=gcc

name=hash

all: ${name}

${name}: ${name}.o main.o ../package.o

clean:
	rm -f *.o
	rm -f ${name}

