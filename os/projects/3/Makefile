.PHONY: clean

CFLAGS=-g
MAIN=main
ADDR=addr
OBJS=vm.o

all: $(MAIN) $(ADDR)

$(MAIN): $(MAIN).c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(ADDR): $(ADDR).c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm -rf *.o *_test $(TARGET) *.zip
