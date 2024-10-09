#ifndef LOG_H
#define LOG_H

typedef enum
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
} log_level_t;

// 初始化日志系统
void log_init(log_level_t level);

// 设置日志级别
void log_set_level(log_level_t level);

// 日志记录函数
void log_write(log_level_t level, const char *format, ...);

#endif // LOG_H
