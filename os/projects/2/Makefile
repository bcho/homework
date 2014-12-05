.PHONY: clean prepare-win

CFLAGS=-g
OBJS=job.o resource.o tick.o fcfs_sched.o sjf_sched.o hrn_sched.o tick.o
TARGET=main

$(TARGET): $(TARGET).c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o $(TARGET) *.zip

prepare-win:
	./convert.sh
	zip win.zip converted/**
	rm -rf converted
