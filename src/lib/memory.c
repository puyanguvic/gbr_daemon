#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 安全地分配内存，如果失败则退出程序
 *
 * @param size 要分配的字节数
 * @return void* 分配的内存指针
 */
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

/**
 * @brief 安全地分配初始化为零的内存，如果失败则退出程序
 *
 * @param nmemb 元素数量
 * @param size 每个元素的大小
 * @return void* 分配的内存指针
 */
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

/**
 * @brief 安全地重新分配内存，如果失败则退出程序
 *
 * @param ptr 原内存指针
 * @param size 新的大小
 * @return void* 新的内存指针
 */
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

/**
 * @brief 释放内存指针
 *
 * @param ptr 要释放的内存指针
 */
void xfree(void *ptr)
{
    if (ptr)
        free(ptr);
}
