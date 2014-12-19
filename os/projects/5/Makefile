.PHONY: tests clean prepare-win

CFLAGS=-g
TARGET=repl
OBJS=fs.o proc.o sys_call.o utils.o

$(TARGET): $(TARGET).c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

prepare-win:
	./convert.sh
	zip win.zip converted/**
	rm -rf converted

tests: fs_test proc_test sys_call_test
	./fs_test
	./proc_test
	./sys_call_test

fs_test: fs_test.c fs.o proc.o
	$(CC) -o $@ $^ $(CFLAGS)

proc_test: proc_test.c proc.o
	$(CC) -o $@ $^ $(CFLAGS)

sys_call_test: sys_call_test.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o *_test $(TARGET) *.zip
