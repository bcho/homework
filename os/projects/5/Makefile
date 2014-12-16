.PHONY: tests clean

CFLAGS=-g
TARGET=repl
OBJS=fs.o proc.o

tests: fs_test
	./fs_test

fs_test: fs_test.c fs.o proc.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o $(TARGET) *.zip
