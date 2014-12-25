.PHONY: clean

CFLAGS=-g
TARGET=main
OBJS=vm.o

$(TARGET): $(TARGET).c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm -rf *.o *_test $(TARGET) *.zip
