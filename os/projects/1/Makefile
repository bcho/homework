.PHONY: tests

CFLAGS=-lm

build: priority_sched round_robin_sched multiple_queue_sched

tests: proc_test utils_test
	./proc_test
	./utils_test


priority_sched: priority_sched.c proc.c

round_robin_sched: round_robin_sched.c proc.c

multiple_queue_sched: multiple_queue_sched.c proc.c

proc_test: proc_test.c proc.c

utils_test: utils_test.c utils.c
