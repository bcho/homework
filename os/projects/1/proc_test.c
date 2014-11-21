#include <string.h>
#include "lib/miniunit.h"

#include "proc.h"

int tests_run;

char *
test_proc_create_and_destory()
{
    struct proc *p;
    
    p = proc_create(1, 1, 1);
    mu_assert("proc_create: proc", p != NULL);
    mu_assert("proc_create: pid", p->pid == 1);
    mu_assert("proc_create: name", strcmp(p->name, "1") == 0);
    mu_assert("proc_create: priority", p->priority == 1);
    mu_assert("proc_create: state", p->state == WAITING);
    mu_assert("proc_create: ntime", p->ntime == 1);
    mu_assert("proc_create: rtime", p->rtime == 0);
    mu_assert("proc_create: next", p->next == NULL);

    // proc_info(*p);

    proc_destory(p);

    return 0;
}

char *
test_proc_run()
{
    struct proc *p;

    // process that can 2 time slices.
    p = proc_create(1, 1, 2);

    p->state = WAITING;
    mu_assert("proc_run: unrunable", proc_run(p) == - E_UNRUNABLE);
    mu_assert("proc_run: unrunable", p->rtime == 0);

    p->state = FINISHED;
    mu_assert("proc_run: unrunable", proc_run(p) == - E_UNRUNABLE);
    mu_assert("proc_run: unrunable", p->rtime == 0);

    p->state = RUNNING;
    mu_assert("proc_run: runable", proc_run(p) == 1);
    mu_assert("proc_run: update ran time", p->rtime == 1);

    mu_assert("proc_run: runable", proc_run(p) == 1);
    mu_assert("proc_run: update ran time", p->rtime == 2);
    mu_assert("proc_run: update finished state", p->state == FINISHED);

    p->state = RUNNING;
    p->rtime = p->ntime + 1;
    mu_assert("proc_run: run on outage process", proc_run(p) == 0);
    mu_assert("proc_run: update finished state", p->state == FINISHED);

    proc_destory(p);

    return 0;
}

char *
run()
{
    mu_run_test(test_proc_create_and_destory);
    mu_run_test(test_proc_run);

    return 0;
}

TEST_MAIN
