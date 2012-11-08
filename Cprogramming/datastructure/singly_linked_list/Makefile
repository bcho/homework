.PHONY: clean
CCFLAGS=-g

single: singly_linked_list.o main.o
	gcc ${CCFLAGS} singly_linked_list.o main.o -o single

singly_linked_list.o: singly_linked_list.c singly_linked_list.h
	gcc -c ${CCFLAGS} singly_linked_list.c

main.o: main.c
	gcc -c ${CCFLAGS} main.c

clean:
	rm -rf *.o
	rm -rf single
