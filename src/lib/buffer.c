/* TODO: 实现 buffer.c */
#include "buffer.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_INITIAL_CAPACITY 1024

buffer_t *buffer_create(size_t initial_capacity)
{
    buffer_t *buf = (buffer_t *)malloc(sizeof(buffer_t));
    if (!buf)
        return NULL;

    if (initial_capacity == 0)
        initial_capacity = BUFFER_INITIAL_CAPACITY;

    buf->data = (unsigned char *)malloc(initial_capacity);
    if (!buf->data)
    {
        free(buf);
        return NULL;
    }

    buf->size = 0;
    buf->capacity = initial_capacity;
    buf->position = 0;
    return buf;
}

void buffer_free(buffer_t *buf)
{
    if (buf)
    {
        free(buf->data);
        free(buf);
    }
}

int buffer_append(buffer_t *buf, const void *data, size_t len)
{
    if (!buf || !data || len == 0)
        return -1;

    if (buf->size + len > buf->capacity)
    {
        size_t new_capacity = buf->capacity * 2;
        while (new_capacity < buf->size + len)
        {
            new_capacity *= 2;
        }
        if (buffer_resize(buf, new_capacity) != 0)
            return -1;
    }

    memcpy(buf->data + buf->size, data, len);
    buf->size += len;
    return 0;
}

int buffer_read(buffer_t *buf, void *dest, size_t len)
{
    if (!buf || !dest || len == 0)
        return -1;

    if (buf->position + len > buf->size)
        return -1; // 数据不足

    memcpy(dest, buf->data + buf->position, len);
    buf->position += len;
    return 0;
}

void buffer_reset(buffer_t *buf)
{
    if (buf)
    {
        buf->size = 0;
        buf->position = 0;
    }
}

size_t buffer_remaining(buffer_t *buf)
{
    if (!buf)
        return 0;
    return buf->size - buf->position;
}

int buffer_resize(buffer_t *buf, size_t new_capacity)
{
    if (!buf || new_capacity <= buf->capacity)
        return -1;

    unsigned char *new_data = (unsigned char *)realloc(buf->data, new_capacity);
    if (!new_data)
        return -1;

    buf->data = new_data;
    buf->capacity = new_capacity;
    return 0;
}
