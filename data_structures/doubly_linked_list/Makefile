.PHONY: clean

CCFLAGS=-g

all: doubly_linked_list

doubly_linked_list: link.o main.o
	gcc ${CCFLAGS} link.o main.o -o doubly_linked_list

link.o: link.h link.c
	gcc ${CCFLAGS} -c link.c -o link.o

main.o: main.c
	gcc ${CCFLAGS} -c main.c -o main.o

clean:
	rm -f *.o
	rm -f doubly_linked_list

