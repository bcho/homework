// 命令行交互程序
//
// 支持命令：
//
// - d                  显示内存使用情况
// - a size-bytes       分配 size 字节内存
// - f addr             回收起始地址为 addr 的内存块
// - q                  退出程序

#include "config.h"
#include "malloc.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COUNT(a) (sizeof((a)) / sizeof((a[0])))

#define PROMPT_CHAR '>'
#define INPUT_MAX 900           // 输入最大长度
#define ARG_MAX 20              // 参数最大长度
#define ARGS_MAX 80             // 参数最多个数

#define STATUS_OK       0x00        // 执行正常
#define STATUS_ERR      0x01        // 执行异常
#define STATUS_INPUT    0x02        // 输入有误
#define STATUS_EXIT     0xFF        // 退出程序执行


// 系统环境内存块
char *os_mem;

// 内置命令
int display(int, char [ARGS_MAX][ARG_MAX + 1]);
int alloc_memory(int, char [ARGS_MAX][ARG_MAX + 1]);
int free_memory(int, char [ARGS_MAX][ARG_MAX + 1]);
int quit(int, char [ARGS_MAX][ARG_MAX + 1]);
int help(int, char [ARGS_MAX][ARG_MAX + 1]);

typedef int command_func_type(int, char [ARGS_MAX][ARG_MAX + 1]);

struct {
    command_func_type *func;
    const char *name;
    const char *help;
} commands[] = {
    {display,       "d", "显示内存状态"},
    {alloc_memory,  "a", "分配内存"},
    {free_memory,   "f", "回收内存"},
    {quit,          "q", "退出程序"}
};

// 进行用户交互
void repl();

int
main()
{
    // 预先分配系统内存
    if ((os_mem = my_malloc(OS_MEM_SIZE)) == NULL)
        PANIC("初始化失败");
    printf("系统初始化成功\n");

    repl();

    return 0;
}

int
split_args(char * const input, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int arg_length, args_count;
    char *c, *i;

    for (args_count = 0, c = input; *c != 0; c++) {
        for (;*c == ' ' && *c != 0; c++)
            ;

        for (arg_length = 0, i = c; *i != 0 && *i != ' '; i++, arg_length++)
            ;
        arg_length = MIN(arg_length, ARG_MAX);
        strncpy(argv[args_count], c, arg_length);
        argv[args_count++][arg_length] = 0;
        c = i;
    }

    return args_count;
}

void
repl()
{
    int i, command_length, command_rv, argc;
    char argv[ARGS_MAX][ARG_MAX + 1];
    char *inputs;
    command_func_type *command;

    help(0, NULL);
    inputs = NULL;
    while (1) {
        printf("%c ", PROMPT_CHAR);
        getline(&inputs, (size_t *) &i, stdin);

        command = help;
        for (i = 0; i < COUNT(commands); i++) {
            command_length = strlen(commands[i].name);
            if (strncmp(commands[i].name, inputs, command_length) == 0) {
                command = commands[i].func;
                break;
            }
        }

        argc = split_args(inputs, argv);

        command_rv = command(argc, argv);
        switch (command_rv) {
            case STATUS_EXIT:
                return;
            case STATUS_INPUT:
                printf("输入有误\n");
                break;
        }
    }
}

int
display(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    my_display();

    return STATUS_OK;
}

int
alloc_memory(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    long alloc_bytes;
    char *alloc;

    if (argc < 2)
        return STATUS_INPUT;

    alloc_bytes = atol(argv[1]);
    if (alloc_bytes < 0)
        return STATUS_INPUT;

    printf("分配 %d 字节内存\n", alloc_bytes);
    alloc = my_malloc(alloc_bytes);
    if (alloc == NULL) {
        printf("分配失败\n");
        return STATUS_ERR;
    }
    printf("内存分配地址 %p\n", alloc);

    return STATUS_OK;
}

int
free_memory(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    long long addr;

    if (argc < 2)
        return STATUS_INPUT;

    addr = strtoll(argv[1], NULL, 16);
    if (addr < 0)
        return STATUS_INPUT;
    if (addr == (long long) os_mem) {
        printf("不能回收系统环境内存\n");
        return STATUS_INPUT;
    }

    printf("回收 0x%llx 地址处的内存\n", addr);
    my_free((char *) addr);

    return STATUS_OK;
}

int
quit(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    printf("Bye!\n");

    return STATUS_EXIT;
}

int
help(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int i;

    printf("支持命令：\n");
    for (i = 0; i < COUNT(commands); i++)
        printf("  %s:\t%s\n", commands[i].name, commands[i].help);

    return STATUS_OK;
}
