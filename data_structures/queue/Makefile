.PHONY: clean

CCFLAGS=-g
CC=gcc

name=queue

all: ${name}

${name}: ${name}.o main.o
	${CC} ${CCFLAGS} ${name}.o main.o -o ${name}

${name}.o: ${name}.h ${name}.c
	${CC} ${CCFLAGS} -c ${name}.c -o ${name}.o

main.o: main.c
	${CC} ${CCFLAGS} -c main.c -o main.o

clean:
	rm -f *.o
	rm -f ${name}

