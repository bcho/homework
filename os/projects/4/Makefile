.PHONY: build tests clean

CFLAGS=-g

build: repl

repl: repl.c linked_list_malloc.c utils.c

tests: utils_test linked_list_malloc_test
	./utils_test
	./linked_list_malloc_test

utils_test: utils_test.c utils.c


linked_list_malloc_test: malloc_test.c linked_list_malloc.c utils.c
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -rf *_test repl *.o
