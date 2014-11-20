.PHONY: tests

build: priority_sched round_robin_sched multiple_queue_sched

tests: proc_test
	@./proc_test


priority_sched: priority_sched.c proc.c

round_robin_sched: round_robin_sched.c proc.c

multiple_queue_sched: multiple_queue_sched.c proc.c

proc_test: proc_test.c proc.c
