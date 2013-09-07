#include <stdio.h>
#include <sys/resource.h>

void
get_usage()
{
    int who = RUSAGE_SELF;
    struct rusage usage;
    int ret;

    ret = getrusage(who, &usage);

    printf("memory: %ld\n", usage.ru_maxrss);
}
