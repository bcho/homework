.PHONY: clean build prepare_server

CFLAGS=-g

current=01

build: prepare_server client

prepare_server: rename server

rename:
	cp $(current).c server.c

server: unp.c server.c

client: unp.c client.c

clean:
	rm -f server.c
	rm -f *.o
	rm -f client
	rm -f server
