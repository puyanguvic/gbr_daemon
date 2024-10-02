// #ifndef BUFFER_H
// #define BUFFER_H

// #include <stdlib.h>

// // 定义缓冲区结构体
// typedef struct
// {
//     unsigned char *data; // 数据指针
//     size_t length;       // 当前数据长度
//     size_t capacity;     // 缓冲区容量
// } buffer_t;

// // 创建缓冲区
// buffer_t *buffer_create(size_t capacity);

// // 释放缓冲区
// void buffer_free(buffer_t *buffer);

// // 向缓冲区追加数据
// void buffer_append(buffer_t *buffer, const void *data, size_t size);

// // 重置缓冲区（不释放内存）
// void buffer_reset(buffer_t *buffer);

// #endif // BUFFER_H
