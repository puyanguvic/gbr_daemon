
#include "buffer.h"
#include "memory.h"
#include <string.h>

// 创建指定容量的缓冲区
buffer_t *buffer_create(size_t capacity)
{
    buffer_t *buffer = xmalloc(sizeof(buffer_t));
    buffer->data = xmalloc(capacity);
    buffer->length = 0;
    buffer->capacity = capacity;
    return buffer;
}

// 释放缓冲区所占用的内存
void buffer_free(buffer_t *buffer)
{
    if (buffer)
    {
        xfree(buffer->data);
        xfree(buffer);
    }
}

// 向缓冲区追加数据，必要时自动扩容
void buffer_append(buffer_t *buffer, const void *data, size_t size)
{
    // 检查是否需要扩容
    if (buffer->length + size > buffer->capacity)
    {
        buffer->capacity *= 2; // 容量加倍
        buffer->data = xrealloc(buffer->data, buffer->capacity);
    }
    // 复制数据到缓冲区
    memcpy(buffer->data + buffer->length, data, size);
    buffer->length += size;
}

// 重置缓冲区的长度，不释放内存
void buffer_reset(buffer_t *buffer)
{
    buffer->length = 0;
}
