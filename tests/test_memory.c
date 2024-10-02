#include <stdio.h>
#include "memory.h"

int main()
{
    // 测试 xmalloc
    void *ptr = xmalloc(1024);
    if (ptr)
    {
        printf("xmalloc: allocated 1024 bytes\n");
    }

    // 测试 xcalloc
    int *array = xcalloc(10, sizeof(int));
    if (array)
    {
        printf("xcalloc: allocated array of 10 integers\n");
    }

    // 测试 xrealloc
    array = xrealloc(array, 20 * sizeof(int));
    if (array)
    {
        printf("xrealloc: resized array to 20 integers\n");
    }

    // 释放内存
    xfree(ptr);
    xfree(array);

    return 0;
}
