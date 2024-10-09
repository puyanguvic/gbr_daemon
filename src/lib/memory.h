#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

// 内存池类型
typedef struct memory_pool memory_pool_t;

// 创建内存池
memory_pool_t *memory_pool_create(size_t block_size, size_t initial_blocks);

// 销毁内存池
void memory_pool_destroy(memory_pool_t *pool);

// 从内存池中分配内存
void *memory_pool_alloc(memory_pool_t *pool);

// 释放内存池中的内存
void memory_pool_free(memory_pool_t *pool, void *ptr);

// 全局内存分配函数
void *memory_alloc(size_t size);

// 全局内存释放函数
void memory_free(void *ptr);

#endif // MEMORY_H
