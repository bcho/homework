#include "mmu.h"
#include "vm.h"

#include <stdio.h>
#include <string.h>

#define FULLMAGIC ((1 << NPPG) - 1)

struct pg_entry {
    unsigned int ppage;             // 物理页号
    int present;                    // 是否加载到内存中
};


// 物理内存占用情况
unsigned long physical_mem = 0u;

// 页表
struct pg_entry page_table[NVPG];

// 物理内存是否已经用完？
#define IS_PHY_FULL ((physical_mem & FULLMAGIC) == FULLMAGIC)

// 从内存中分配一页
//
// 分配成功返回物理页号。
//
// 如果内存已满返回 -1
static int
phy_alloc()
{
    int i;
    unsigned long mask;

    if (IS_PHY_FULL)
        return -1;

    for (i = 0, mask = 1; i < NPPG; i++, mask = mask << 1) {
        if (mask & physical_mem)
            continue;
        physical_mem = physical_mem | mask;
        return i;
    }

    return -1;
}

// 从内存中清除一页
//
// @param 物理页数
static void
phy_disalloc(unsigned int ppg)
{
    physical_mem = physical_mem & (~ (1 << ppg));
}

// 打印物理内存页面情况
static void
phy_dump()
{
    int i;
    unsigned int mask;

    printf("物理内存页面情况：\n");
    for (i = 0, mask = 1; i < NPPG; i++, mask = mask << 1) {
        printf("\t页面 %03d: ", i);
        if (mask & physical_mem)
            printf("被占用");
        else
            printf("未占用");
        if (i % 4 == 3)
            printf("\n");
    }
}

void
vm_init()
{
    physical_mem = 0u;
    memset(page_table, 0, NVPG * sizeof(struct pg_entry));
}

void
vm_alloc(unsigned int vpage)
{
    int ppage;

    if ((ppage = phy_alloc()) == -1) {
        // TODO swap out a page
        printf("内存已满\n");
        vm_dump();

        return;
    }

    page_table[vpage].ppage == ppage;
    page_table[vpage].present = 1;
}


void
vm_hit(unsigned int va)
{
    unsigned vpage, pa;

    // TODO boundary check
    
    printf("访问虚拟内存地址: 0x%04x\n", va);
    vpage = PTX(va);
    if (page_table[vpage].present) {
        pa = PPA(page_table[vpage].ppage, VAO(va));
        printf("访问物理内存地址: 0x%04x\n", pa);
    } else {
        // page fault
        printf("页面 %d 不在内存中\n", vpage);
        vm_alloc(vpage);

        // vm_hit(va);
    }
}

void
vm_dump()
{
    int i;

    printf("=============================================\n");
    phy_dump(); printf("\n");

    printf("虚拟内存页面情况：\n");
    for (i = 0; i < NVPG; i++) {
        printf("\t页面 %03d: ", i);
        if (page_table[i].present)
            printf("已加载");
        else
            printf("未加载");
        if (i % 4 == 3)
            printf("\n");
    }
    printf("=============================================\n");
}
