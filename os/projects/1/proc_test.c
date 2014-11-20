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
    mu_assert("proc_create: pprev", p->pprev== NULL);
    mu_assert("proc_create: next", p->next == NULL);

    // proc_info(*p);

    proc_destory(p);

    return 0;
}

char *
run()
{
    mu_run_test(test_proc_create_and_destory);

    return 0;
}

TEST_MAIN
