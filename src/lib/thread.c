#include "thread.h"
#include <stdlib.h>

// 创建线程并启动
int thread_create(thread_t *thread, thread_func_t func, void *arg)
{
    thread->func = func; // 设置线程函数
    thread->arg = arg;   // 设置传递给线程函数的参数
    // 调用 pthread_create 创建线程
    return pthread_create(&thread->pthread, NULL, func, arg);
}

// 等待线程结束
void thread_join(thread_t *thread)
{
    // 调用 pthread_join 等待线程执行完毕
    pthread_join(thread->pthread, NULL);
}
