#include "memory.h"
#include <stdio.h>

// 分配内存，如果失败则打印错误并退出
void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        fprintf(stderr, "xmalloc: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// 分配初始化为零的内存
void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (!ptr)
    {
        fprintf(stderr, "xcalloc: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// 重新分配内存
void *xrealloc(void *ptr, size_t size)
{
    ptr = realloc(ptr, size);
    if (!ptr)
    {
        fprintf(stderr, "xrealloc: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// 释放内存
void xfree(void *ptr)
{
    if (ptr)
        free(ptr);
}
