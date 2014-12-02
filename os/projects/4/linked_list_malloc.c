// 链表实现的 malloc
//
// 内存块结果：
//
// +------+------------------------+
// | 块头 |         块体           |
// +------+------------------------+
//
// 块头包含：
//
// - 内存块体大小
// - 内存块是否被使用
// - 内存块链上/下一个块

#include "malloc.h"
#include "utils.h"

#include <stddef.h>
#include <stdio.h>

struct mb_header {
    size_t size;                // 内存块体大小
    int in_use;                 // 内存块是否被使用

    struct mb_header *prev;     // 上一个内存块
    struct mb_header *next;     // 下一个内存块
};

#define MB_HEADER_SIZE ALIGN(sizeof(struct mb_header))

// 遍历内存块循环链表
//
// @param 循环遍历
// @param 链表头
#define mb_header_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

// 插入到内存块循环链表
//
// @param 插入点的前继结点
// @param 插入内存块
#define mb_header_insert(p, n) \
    do { \
        n->next = (p)->next; \
        (p)->next = n; \
        n->prev = (p); \
        n->next->prev = n; \
    } while (0)

// 从循环链表中删除一个结点
//
// @param 删除结点
#define mb_header_delete(n) \
    do { \
        (n)->prev->next = (n)->next; \
        (n)->next->prev = (n)->prev; \
    } while (0)


// 内存块循环链表头结点
struct mb_header *mb_head = NULL;


// 初始化内存块链表
static void
init()
{
    mb_head = u_sbrk(MB_HEADER_SIZE);
    if (mb_head == E_SBRK)
        PANIC("初始化内存块链表失败");

    mb_head->size = 0;
    mb_head->in_use = 1;
    mb_head->prev = mb_head;
    mb_head->next = mb_head;
}


// 获取一个合适的内存块
//
// 如果没有找到合适内存块，返回 NULL
//
// @param 需要的内存块大小
static inline struct mb_header *
mb_header_find_fit(size_t requested_size)
{
    struct mb_header *p, *nb;

    mb_header_for_each(p, mb_head)
        if (!p->in_use && p->size >= requested_size) {

            // 分割内存块
            if (p->size > requested_size + MB_HEADER_SIZE) {
                nb = (struct mb_header *) ((char *) p + MB_HEADER_SIZE + requested_size);
                nb->size = p->size - requested_size - MB_HEADER_SIZE;
                p->size = requested_size;
                nb->in_use = 0;
                mb_header_insert(p, nb);
            }

            return p;
        }

    return NULL;
}


void *
my_malloc(size_t size)
{
    static int initialized = 0;
    if (!initialized) {                 // 初始化内存块链表
        initialized = 1;
        init();
    }

    size_t *block;
    struct mb_header *block_header;

    // 对齐块的大小
    size = ALIGN(size);

    block_header = mb_header_find_fit(size);

    // 没有找到合适的内存块，新建一块
    if (block_header == NULL) {
        block = u_sbrk(ALIGN(size + MB_HEADER_SIZE));
        if (block == E_SBRK)
            return NULL;

        block_header = (struct mb_header *) block;
        block_header->size = size;
        block_header->in_use = 0;
        
        // 插入到内存块链表的尾部
        mb_header_insert(mb_head->prev, block_header);
    }

    block_header->in_use = 1;
    
    return (char *) block_header + MB_HEADER_SIZE;
}

void
my_free(void *mem)
{
    struct mb_header *block_header, *other;

    block_header = (struct mb_header *) ((char *) mem - MB_HEADER_SIZE);

    if (! block_header->in_use)
        PANIC("double free");

    block_header->in_use = 0;

    // 合并相邻空余的内存块（前面的块合并后面的块）
    while (block_header != mb_head) {
        other = block_header->next;
        if (other == mb_head || other->in_use)
            break;
        mb_header_delete(other);
        block_header->size = block_header->size + other->size + MB_HEADER_SIZE;
    }
    while (block_header != mb_head) {
        other = block_header->prev;
        if (other == mb_head || other->in_use)
            break;
        mb_header_delete(block_header);
        other->size = other->size + block_header->size + MB_HEADER_SIZE;
        block_header = other;
    }
}

void
display_mb(struct mb_header *b)
{
    printf("+----------------------------------+\n");
    printf("| 起始地址: 0x%llx\n", (long long) ((char *) b + MB_HEADER_SIZE));
    printf("| 内存大小: %d bytes\n", (int) b->size);
    printf("| 是否被使用: %d \n", b->in_use);
    printf("+----------------------------------+\n");
}

void
my_display()
{
    struct mb_header *p;

    if (mb_head == NULL)
        init();

    printf("内存使用情况：\n");
    mb_header_for_each(p, mb_head)
        display_mb(p);
}
