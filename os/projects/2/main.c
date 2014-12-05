#include "structure.h"
#include "job.h"
#include "resource.h"
#include "tick.h"
#include "sched.h"
#include "utils.h"

int
main()
{
    struct resource *sys_r = resource_create("内存", 20);
    struct resource *r = resource_create("内存", 20);
    struct resource *r2 = resource_create("内存", 20);
    struct resource *r3 = resource_create("内存", 20);
    struct job *j = job_create("A", "1", 5, 20, r);
    struct job *j2 = job_create("A", "2", 0, 20, r2);
    struct job *j3 = job_create("A", "3", 100, 20, r3);

    llist_insert_after(j, j2);
    llist_insert_after(j2, j3);

    tick(sys_r, &j, fcfs_scheduler);

    llist_for_each(j2, j)
        job_info(j2);

    return 0;
}
