#include "log.h"
#include <assert.h>
#include <stdio.h>

void test_log_levels()
{
    printf("Running test_log...\n");
    log_init(LOG_LEVEL_DEBUG);

    // Testing different log levels
    log_debug("This is a debug message");
    log_info("This is an info message");
    log_warn("This is a warning message");
    log_error("This is an error message");

    // Setting log level to WARN, debug and info should not be printed
    log_set_level(LOG_LEVEL_WARN);
    log_debug("This debug message should not be printed");
    log_info("This info message should not be printed");
    log_warn("This warning message should be printed");
    log_error("This error message should be printed");

    printf("All log tests passed.\n");
}

int main()
{
    test_log_levels();
    return 0;
}
