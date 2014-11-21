.PHONY: build tests clean

CFLAGS=-lm -g

build: priority_sched round_robin_sched multiple_queue_sched

tests: proc_test utils_test
	./proc_test
	./utils_test


priority_sched: priority_sched.c proc.c utils.c

round_robin_sched: round_robin_sched.c proc.c utils.c

multiple_queue_sched: multiple_queue_sched.c proc.c utils.c

proc_test: proc_test.c proc.c utils.c

utils_test: utils_test.c utils.c utils.c

clean:
	rm -rf *_sched *_test
