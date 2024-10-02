#ifndef LOG_H
#define LOG_H

#include <stdio.h>

// 定义日志级别
typedef enum
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

// 初始化日志系统，设置日志级别
void log_init(log_level_t level);

// 日志输出函数，支持格式化字符串
void log_message(log_level_t level, const char *format, ...);

// 定义方便使用的日志宏
#define log_debug(format, ...) log_message(LOG_DEBUG, format, ##__VA_ARGS__)
#define log_info(format, ...) log_message(LOG_INFO, format, ##__VA_ARGS__)
#define log_warn(format, ...) log_message(LOG_WARN, format, ##__VA_ARGS__)
#define log_error(format, ...) log_message(LOG_ERROR, format, ##__VA_ARGS__)

#endif // LOG_H
