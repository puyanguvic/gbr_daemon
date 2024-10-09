/* TODO: 实现 log.c */
#include "log.h"
#include <stdio.h>
#include <stdarg.h>

static log_level_t current_level = LOG_LEVEL_INFO;

void log_init(log_level_t level)
{
    current_level = level;
}

void log_set_level(log_level_t level)
{
    current_level = level;
}

void log_write(log_level_t level, const char *format, ...)
{
    if (level < current_level)
        return;

    const char *level_str = "";
    switch (level)
    {
    case LOG_LEVEL_DEBUG:
        level_str = "DEBUG";
        break;
    case LOG_LEVEL_INFO:
        level_str = "INFO";
        break;
    case LOG_LEVEL_WARN:
        level_str = "WARN";
        break;
    case LOG_LEVEL_ERROR:
        level_str = "ERROR";
        break;
    }

    printf("[%s] ", level_str);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n");
}
