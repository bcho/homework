.PHONY: tests clean

CFLAGS=-g
OBJS=mem_dev.o fs.o
TARGET=os

$(TARGET): $(TARGET).c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

os: os.c

tests: mem_dev_test
	./mem_dev_test


mem_dev_test: mem_dev_test.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm -rf *.o $(TARGET) *.zip
