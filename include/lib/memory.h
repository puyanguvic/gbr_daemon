#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

// 带有错误检查的内存分配函数
void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *ptr, size_t size);
void xfree(void *ptr);

#endif // MEMORY_H
