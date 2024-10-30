#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

// Log levels
typedef enum
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} log_level_t;

// Function declarations
void log_init(log_level_t level);
void log_set_level(log_level_t level);
void log_write(log_level_t level, const char *format, ...);

// Macros for convenience
#define log_debug(format, ...) log_write(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define log_info(format, ...) log_write(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define log_warn(format, ...) log_write(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define log_error(format, ...) log_write(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)

#endif // LOG_H