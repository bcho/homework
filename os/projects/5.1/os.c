#include "fs.h"
#include "mem_dev.h"

int
main()
{
    mem_dev_init(MEM_FS_SIZE);
    fs_init();

    return 0;
}
