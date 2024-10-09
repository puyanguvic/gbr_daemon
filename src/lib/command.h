#ifndef COMMAND_H
#define COMMAND_H

typedef struct command
{
    const char *name;
    int (*handler)(int argc, char **argv);
    const char *help;
} command_t;

// 注册命令
int command_register(command_t *cmd);

// 执行命令
int command_execute(const char *line);

// 初始化命令系统
void command_init(void);

// 清理命令系统
void command_cleanup(void);

#endif // COMMAND_H
