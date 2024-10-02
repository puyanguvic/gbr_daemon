// #ifndef THREAD_H
// #define THREAD_H

// #include <pthread.h>

// // 定义线程函数类型，接受 void* 参数，返回 void*，用于 pthread_create
// typedef void *(*thread_func_t)(void *);

// // 线程结构体，封装 pthread_t 和线程函数信息
// typedef struct thread
// {
//     pthread_t pthread;  // POSIX 线程标识符
//     thread_func_t func; // 线程函数指针
//     void *arg;          // 传递给线程函数的参数
// } thread_t;

// // 创建线程函数的声明
// int thread_create(thread_t *thread, thread_func_t func, void *arg);

// // 等待线程结束函数的声明
// void thread_join(thread_t *thread);

// #endif // THREAD_H
