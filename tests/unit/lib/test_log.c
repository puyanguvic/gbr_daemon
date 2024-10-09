#include "log.h"
#include <stdio.h>

int main(void)
{
    printf("Running test_log...\n");

    log_init(LOG_LEVEL_DEBUG);

    log_write(LOG_LEVEL_DEBUG, "This is a debug message.");
    log_write(LOG_LEVEL_INFO, "This is an info message.");
    log_write(LOG_LEVEL_WARN, "This is a warning message.");
    log_write(LOG_LEVEL_ERROR, "This is an error message.");

    log_set_level(LOG_LEVEL_WARN);

    log_write(LOG_LEVEL_DEBUG, "This debug message should not appear.");
    log_write(LOG_LEVEL_INFO, "This info message should not appear.");
    log_write(LOG_LEVEL_WARN, "This warning message should appear.");
    log_write(LOG_LEVEL_ERROR, "This error message should appear.");

    printf("All log tests passed.\n");
    return 0;
}
