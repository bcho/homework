.PHONY: clean

CCFLAGS=-g
CC=gcc

prog_name=polynomial
datastructure=link

all: ${prog_name}

${prog_name}: ${datastructure}.o ${prog_name}.o main.o
	${CC} ${CCFLAGS} ${prog_name}.o ${datastructure}.o main.o -o ${prog_name}

${datastructure}.o: ${datastructure}.h ${datastructure}.c
	${CC} ${CCFLAGS} -c ${datastructure}.c -o ${datastructure}.o

${prog_name}.o: ${prog_name}.h ${prog_name}.c
	${CC} ${CCFLAGS} -c ${prog_name}.c -o ${prog_name}.o

main.o: main.c
	${CC} ${CCFLAGS} -c main.c -o main.o

clean:
	rm -f *.o
	rm -f ${prog_name}

