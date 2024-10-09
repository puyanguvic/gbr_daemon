#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

typedef struct buffer
{
    unsigned char *data; // 缓冲区数据指针
    size_t size;         // 当前缓冲区大小
    size_t capacity;     // 缓冲区总容量
    size_t position;     // 当前读写位置
} buffer_t;

// 创建新的缓冲区
buffer_t *buffer_create(size_t initial_capacity);

// 释放缓冲区
void buffer_free(buffer_t *buf);

// 向缓冲区追加数据
int buffer_append(buffer_t *buf, const void *data, size_t len);

// 从缓冲区读取数据
int buffer_read(buffer_t *buf, void *dest, size_t len);

// 重置缓冲区（清空数据）
void buffer_reset(buffer_t *buf);

// 获取缓冲区中的剩余数据大小
size_t buffer_remaining(buffer_t *buf);

// 调整缓冲区容量
int buffer_resize(buffer_t *buf, size_t new_capacity);

#endif // BUFFER_H
