#include "vm.h"
#include "config.h"

int
main()
{
    int i;

    vm_init();

    for (i = 0; i < VMEM; i++)
        vm_hit(i);
    vm_dump();

    return 0;
}
