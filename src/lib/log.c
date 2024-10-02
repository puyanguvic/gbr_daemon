#include "log.h"
#include <stdarg.h>
#include <time.h>

// 全局变量，记录当前的日志级别
static log_level_t current_level = LOG_DEBUG;

// 初始化日志系统，设置日志级别
void log_init(log_level_t level)
{
    current_level = level;
}

// 日志输出函数，带有时间戳和日志级别
void log_message(log_level_t level, const char *format, ...)
{
    // 如果日志级别低于当前设置，则不输出
    if (level < current_level)
        return;

    // 定义日志级别字符串表示
    const char *level_str[] = {"DEBUG", "INFO", "WARN", "ERROR"};
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // 输出时间戳和日志级别
    printf("[%04d-%02d-%02d %02d:%02d:%02d][%s] ",
           t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
           t->tm_hour, t->tm_min, t->tm_sec,
           level_str[level]);

    // 处理可变参数，输出日志信息
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\n");
}
