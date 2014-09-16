OBJS = bison.o lex.o

CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

a_plus_b: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o a_plus_b -lfl

lex.o: lex.c bison.o
	$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c: a_plus_b.flex
	flex a_plus_b.flex
	mv lex.yy.c lex.c

bison.o: bison.c
	$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c: a_plus_b.y
	bison -d -v a_plus_b.y
	mv a_plus_b.tab.c bison.c
	mv a_plus_b.tab.h tokens.h

lex.o: a_plus_b.h

clean:
	rm -rf *.o lex.c lex.yy.c bison.c tokens.h a_plus_b.output a_plus_b.c a_plus_b
