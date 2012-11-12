.PHONY: clean

CCFLAGS=-g
CC=gcc ${CCFLAGS}

all: stack

stack: stack.o main.o
	${CC} stack.o main.o -o stack

stack.o: stack.h stack.c
	${CC} -c stack.c -o stack.o

main.o: main.c
	${CC} -c main.c -o main.o

clean:
	rm -f *.o
	rm -f stack

