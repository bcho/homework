#include "mmu.h"
#include "vm.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define FULLMAGIC ((1 << NPPG) - 1)

struct pg_entry {
    unsigned int ppage;             // 物理页号
    int present;                    // 是否加载到内存中
};


// 物理内存占用情况
unsigned long physical_mem = 0u;

// 指向当前可以替换的物理内存页
unsigned int victim_ppage = 0u;

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
    victim_ppage = 0u;
    memset(page_table, 0, NVPG * sizeof(struct pg_entry));
}

void
vm_alloc(unsigned int vpage)
{
    int ppage, i;

    if ((ppage = phy_alloc()) == -1) {
        printf("内存已满\n");

        // 当前使用 FIFO 算法来进行替换
        //
        // TODO 支持其他算法 (esp. LRU)
        printf("替换物理内存页：%d\n", victim_ppage);
        phy_disalloc(victim_ppage);
        for (i = 0; i < NVPG; i++)
            if (page_table[i].present && page_table[i].ppage == victim_ppage)
                page_table[i].present = 0;

        // 使用该页
        ppage = phy_alloc();
        assert(ppage != -1);

        // 更新可替换页
        victim_ppage = (victim_ppage + 1) % NPPG;
    }

    printf("分配虚拟内存页：%d <- %d\n", vpage, ppage);
    page_table[vpage].ppage = ppage;
    page_table[vpage].present = 1;
}

void
vm_hit(unsigned int va)
{
    unsigned vpage, pa;

    // TODO boundary check
    
    fprintf(stderr, "访问虚拟内存地址: 0x%04x\n", va);
    vpage = PTX(va);
    if (page_table[vpage].present) {
        pa = PPA(page_table[vpage].ppage, VAO(va));
        fprintf(stderr, "访问物理内存地址: 0x%04x\n", pa);
    } else {
        // page fault
        printf("虚拟内存页 %d 不在内存中\n", vpage);
        vm_alloc(vpage);

        vm_hit(va);
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
            printf("已加载 %d", page_table[i].ppage);
        else
            printf("未加载");
        if (i % 4 == 3)
            printf("\n");
    }
    printf("=============================================\n");
}
