// 命令行交互程序
//
// 支持命令：
//
// - bye                    退出系统
// - ls                     打印文件系统
// - create path            创建文件
//  * close                     关闭文件
//  * read                      读取文件
//  * write content             写入文件
// - open path              打开文件
//  * close                     关闭文件
//  * read                      读取文件
//  * write content             写入文件
// - delete path            删除文件

#include "sys_call.h"
#include "proc.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define COUNT(a) (sizeof((a)) / sizeof((a[0])))

#define PROMPT_CHAR '>'
#define INPUT_MAX 900           // 输入最大长度
#define ARG_MAX 20              // 参数最大长度
#define ARGS_MAX 80             // 参数最多个数

#define STATUS_OK       0x00        // 执行正常
#define STATUS_ERR      0x01        // 执行异常
#define STATUS_INPUT    0x02        // 输入有误
#define STATUS_EXIT     0xFF        // 退出程序执行

// 用户列表
const char *USERS[] = {
    "hbc",
    "alice"
};

// 内置命令
int command_bye(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_ls(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_create(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_open(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_close(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_read(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_write(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_delete(int, char [ARGS_MAX][ARG_MAX + 1]);
int command_help(int, char [ARGS_MAX][ARG_MAX + 1]);

typedef int command_func_type(int, char [ARGS_MAX][ARG_MAX + 1]);

struct {
    command_func_type *func;
    const char *name;
    const char *help;
} commands[] = {
    {command_bye,       "bye",      "退出系统"},
    {command_ls,        "ls",       "打印文件系统"},
    {command_create,    "create",   "创建文件"},
    {command_open,      "open",     "打开文件"},
    {command_close,     "close",    "关闭文件"},
    {command_read,      "read",     "读取文件内容"},
    {command_write,     "write",    "写入内容到文件"},
    {command_delete,    "delete",   "删除文件"}
};

// 进行用户交互
void repl();

#define FD_MAGIC 0xbeef         // It's magic!

// 当前打开文件描述符
int current_fd;
// 当前用户
struct user current_user;

// 文件内容
char content_buffer[CONTENT_SIZE];

int
main()
{
    int i, flag;
    char home_dir[NAME_LENGTH + 2];
    char *username;
    size_t username_size;

    current_fd = FD_MAGIC;
    memset(content_buffer, 0, CONTENT_SIZE);

    // 初始化文件系统
    if (init() != E_OK)
        PANIC("文件系统初始化失败");

    // 根据配置创建用户和对应用户文件夹
    for (i = 0; i < COUNT(USERS); i++) {
        printf("初始化用户目录: %s\n", USERS[i]);
        if (user_get_by_id(useradd(USERS[i]), &current_user) != E_OK)
            PANIC("初始化用户失败");
        sprintf(home_dir, "/%s", current_user.name);
        if (create(&current_user,
                   TYPE_DIR,
                   home_dir,
                   PERM_RD | PERM_WR,
                   PERM_RD) != E_OK)
            PANIC("初始化用户失败");
    }

    printf("文件系统初始化成功\n");

    // 登录用户
    flag = 1;
    while (flag) {
        printf("输入用户名： ");
        username_size = 0;
        u_getline(&username, &username_size, stdin);

        for (i = 0; i < COUNT(USERS); i++)
            if (strcmp(USERS[i], username) == 0) {
                if (user_get_by_id(i + 2, &current_user) != E_OK)
                    PANIC("获取用户失败");
                flag = 0;
                break;
            }

        if (flag)
            printf("没有找到用户： %s\n", username);
    }

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
    size_t inputs_size;
    command_func_type *command;

    command_help(0, NULL);
    inputs = NULL;
    while (1) {
        printf("%c ", PROMPT_CHAR);
        inputs_size = 0;
        u_getline(&inputs, &inputs_size, stdin);

        command = command_help;
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
command_help(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int i;

    printf("当前用户：%s\n", current_user.name);
    printf("支持命令：\n");
    for (i = 0; i < COUNT(commands); i++)
        printf("  %s:\n\t%s\n", commands[i].name, commands[i].help);

    return STATUS_OK;
}

int
command_bye(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    printf("bye!\n");

    return STATUS_EXIT;
}

#define NEED_FD \
    do { \
        if (current_fd == FD_MAGIC) { \
            printf("请先使用 create / open 命令打开一个文件\n"); \
            return STATUS_OK; \
        } \
    } while (0)


#define CLOSE_FD \
    do { \
        if (current_fd != FD_MAGIC) \
            if (close(current_fd) != E_OK) \
                PANIC("关闭失败"); \
        current_fd = FD_MAGIC; \
    } while (0)

int
command_create(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int rv;

    if (argc < 2)
        return STATUS_INPUT;

    // TODO 允许指定权限
    rv = - create(&current_user, TYPE_FILE, argv[1], PERM_RD | PERM_WR, PERM_RD);
    switch (rv) {
        case E_FAIL:
            printf("创建 %s 失败\n", argv[1]);
            break;
        case E_PERMISSION:
            printf("权限不足\n");
            break;
        case E_OK:
            printf("文件创建成功\n");
            CLOSE_FD;
            current_fd = open(&current_user, argv[1], PERM_WR);
            break;
        default:
            printf("未知错误: %d\n", rv);
    }

    stat_fs(&current_user);
    return STATUS_OK;
}

int
command_open(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int rv;

    if (argc < 2)
        return STATUS_INPUT;

    CLOSE_FD;

    rv = open(&current_user, argv[1], PERM_RD);
    switch (- rv) {
        case E_FAIL:
            printf("打开 %s 失败\n", argv[1]);
            break;
        case E_PERMISSION:
            printf("权限错误\n");
            break;
        case E_INVALID_TYPE:
            printf("打开 %s 失败\n", argv[1]);
            break;
        default:
            current_fd = rv;
            printf("文件打开成功\n");
    }

    return STATUS_OK;
}

int
command_close(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    NEED_FD;

    if (current_fd != FD_MAGIC && close(current_fd) == E_OK)
        printf("文件已经关闭\n");
    current_fd = FD_MAGIC;

    return STATUS_OK;
}

int
command_read(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int rv;

    NEED_FD;

    rv = read(current_fd, content_buffer);
    switch (- rv) {
        case E_FAIL:
            printf("读取失败\n");
            break;
        default:
            if (rv >= 0)
                printf("%s\n", content_buffer);
            else
                printf("未知错误：%d\n", rv);
    }

    return STATUS_OK;
}

int
command_write(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int rv;

    NEED_FD;

    if (argc < 2)
        return STATUS_INPUT;

    rv = write(current_fd, argv[1]);
    switch (- rv) {
        case E_FAIL:
            printf("写入失败\n");
            break;
        default:
            if (rv >= 0)
                printf("写入成功\n");
            else
                printf("未知错误：%d\n", rv);
    }

    return STATUS_OK;
}

int
command_delete(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    int rv;

    CLOSE_FD;

    if (argc < 2)
        return STATUS_INPUT;

    rv = - delete(&current_user, argv[1]);
    switch (rv) {
        case E_OK:
            printf("删除 %s 成功\n", argv[1]);
            break;
        case E_FAIL:
            printf("删除失败\n");
            break;
        case E_PERMISSION:
            printf("权限不足\n");
            break;
        default:
            printf("未知错误： %d\n", rv);
    }

    return STATUS_OK;
}

int
command_ls(int argc, char argv[ARGS_MAX][ARG_MAX + 1])
{
    stat_fs(&current_user);

    return STATUS_OK;
}
