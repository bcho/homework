.PHONY: clean

all: singly_linked_list

singly_linked_list: link.o main.o
	gcc link.o main.o -o singly_linked_list

link.o: link.h link.c
	gcc -c link.c -o link.o

main.o: main.c
	gcc -c main.c -o main.o

clean:
	rm -f *.o
	rm -f singly_linked_list

