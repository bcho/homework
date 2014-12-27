#include "vm.h"
#include "config.h"

#include <stdio.h>

int
main()
{
    int cont, addr;

    vm_init();

    cont = 1;
    while (cont) {
        scanf("%d", &addr);

        switch (addr) {
            case INST_FINISH:
                cont = 0;
                break;
            case INST_VMDUMP:
                vm_dump();
                break;
            default:
                vm_hit(addr);
        }
    }

    return 0;
}
