#include "memory.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct memory_block
{
    struct memory_block *next;
};

struct memory_pool
{
    size_t block_size;
    struct memory_block *free_list;
    pthread_mutex_t lock;
};

memory_pool_t *memory_pool_create(size_t block_size, size_t initial_blocks)
{
    memory_pool_t *pool = (memory_pool_t *)malloc(sizeof(memory_pool_t));
    if (!pool)
        return NULL;

    pool->block_size = block_size > sizeof(struct memory_block *) ? block_size : sizeof(struct memory_block *);
    pool->free_list = NULL;
    pthread_mutex_init(&pool->lock, NULL);

    // 预分配初始块
    for (size_t i = 0; i < initial_blocks; i++)
    {
        struct memory_block *block = (struct memory_block *)malloc(pool->block_size);
        if (block)
        {
            block->next = pool->free_list;
            pool->free_list = block;
        }
    }

    return pool;
}

void memory_pool_destroy(memory_pool_t *pool)
{
    if (!pool)
        return;

    pthread_mutex_lock(&pool->lock);
    struct memory_block *block = pool->free_list;
    while (block)
    {
        struct memory_block *next = block->next;
        free(block);
        block = next;
    }
    pthread_mutex_unlock(&pool->lock);

    pthread_mutex_destroy(&pool->lock);
    free(pool);
}

void *memory_pool_alloc(memory_pool_t *pool)
{
    if (!pool)
        return NULL;

    pthread_mutex_lock(&pool->lock);
    struct memory_block *block = pool->free_list;
    if (block)
    {
        pool->free_list = block->next;
        pthread_mutex_unlock(&pool->lock);
        return block;
    }
    else
    {
        pthread_mutex_unlock(&pool->lock);
        return malloc(pool->block_size);
    }
}

void memory_pool_free(memory_pool_t *pool, void *ptr)
{
    if (!pool || !ptr)
        return;

    pthread_mutex_lock(&pool->lock);
    struct memory_block *block = (struct memory_block *)ptr;
    block->next = pool->free_list;
    pool->free_list = block;
    pthread_mutex_unlock(&pool->lock);
}

void *memory_alloc(size_t size)
{
    return malloc(size);
}

void memory_free(void *ptr)
{
    free(ptr);
}
