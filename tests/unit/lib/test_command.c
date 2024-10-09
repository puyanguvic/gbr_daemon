#include <stdio.h>
#include "command.h"

int test_cmd_handler(int argc, char **argv)
{
    printf("test_cmd_handler called with %d args.\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("Arg %d: %s\n", i, argv[i]);
    }
    return 0;
}

int main(void)
{
    printf("Running test_command...\n");

    command_init();

    command_t test_cmd = {
        .name = "test",
        .handler = test_cmd_handler,
        .help = "Test command"};

    if (command_register(&test_cmd) != 0)
    {
        printf("Failed to register command.\n");
        return 1;
    }

    if (command_execute("test arg1 arg2") != 0)
    {
        printf("Command execution failed.\n");
        return 1;
    }

    command_cleanup();

    printf("All command tests passed.\n");
    return 0;
}
