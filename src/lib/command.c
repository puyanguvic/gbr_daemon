/* TODO: 实现 command.c */
#include "command.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_COMMANDS 100

static command_t *command_list[MAX_COMMANDS];
static int command_count = 0;

void command_init(void)
{
    command_count = 0;
    memset(command_list, 0, sizeof(command_list));
}

void command_cleanup(void)
{
    // 如果有动态分配的资源，需要在这里清理
}

int command_register(command_t *cmd)
{
    if (command_count >= MAX_COMMANDS)
        return -1;
    command_list[command_count++] = cmd;
    return 0;
}

int command_execute(const char *line)
{
    if (!line)
        return -1;

    char *line_copy = strdup(line);
    char *token = strtok(line_copy, " ");
    if (!token)
    {
        free(line_copy);
        return -1;
    }

    for (int i = 0; i < command_count; i++)
    {
        if (strcmp(token, command_list[i]->name) == 0)
        {
            // 匹配命令，解析参数
            char *argv[10];
            int argc = 0;
            argv[argc++] = token;
            while ((token = strtok(NULL, " ")) != NULL && argc < 10)
            {
                argv[argc++] = token;
            }
            int result = command_list[i]->handler(argc, argv);
            free(line_copy);
            return result;
        }
    }

    printf("Unknown command: %s\n", line);
    free(line_copy);
    return -1;
}
