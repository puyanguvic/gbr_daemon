#include <stdio.h>
#include "memory.h"

int main(void)
{
    printf("Running test_memory...\n");

    // 测试内存池
    memory_pool_t *pool = memory_pool_create(64, 10);
    if (!pool)
    {
        printf("Failed to create memory pool.\n");
        return 1;
    }

    void *ptrs[20];
    for (int i = 0; i < 20; i++)
    {
        ptrs[i] = memory_pool_alloc(pool);
        if (!ptrs[i])
        {
            printf("Failed to allocate from memory pool.\n");
            memory_pool_destroy(pool);
            return 1;
        }
    }

    for (int i = 0; i < 20; i++)
    {
        memory_pool_free(pool, ptrs[i]);
    }

    memory_pool_destroy(pool);
    printf("Memory pool test passed.\n");

    // 测试全局内存分配
    void *ptr = memory_alloc(128);
    if (!ptr)
    {
        printf("Failed to allocate memory.\n");
        return 1;
    }
    memory_free(ptr);
    printf("Global memory allocation test passed.\n");

    printf("All memory tests passed.\n");
    return 0;
}
