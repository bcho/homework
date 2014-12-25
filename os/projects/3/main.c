#include "vm.h"
#include "config.h"

int
main()
{
    int i;

    vm_init();
    vm_dump();
    vm_hit(0x1012);
    vm_dump();

    for (i = VMEM - 1; i > 0; i--)
        vm_hit(i);
    vm_dump();

    return 0;
}
