.PHONY: clean

CFLAGS=-g
CC=gcc

all: game

game: grid.o io.o

grid_test: grid_test.c grid.o io.o

io_test: io_test.c grid.o io.o grid.o

clean:
	rm -f *.o
	rm grid_test
	rm io_test
