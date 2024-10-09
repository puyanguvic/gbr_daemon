#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

/**
 * @brief Thread function type.
 */
typedef void *(*thread_func_t)(void *arg);

/**
 * @brief Thread structure.
 */
typedef struct
{
    pthread_t thread_id; // Thread identifier
} thread_t;

/**
 * @brief Mutex structure.
 */
typedef struct
{
    pthread_mutex_t mutex;
} mutex_t;

/**
 * @brief Condition variable structure.
 */
typedef struct
{
    pthread_cond_t cond;
} cond_var_t;

/**
 * @brief Create a new thread.
 *
 * @param thread Pointer to thread structure.
 * @param func Thread function to execute.
 * @param arg Argument to pass to the thread function.
 * @return 0 on success, non-zero on failure.
 */
int thread_create(thread_t *thread, thread_func_t func, void *arg);

/**
 * @brief Join a thread.
 *
 * @param thread Pointer to thread structure.
 * @return 0 on success, non-zero on failure.
 */
int thread_join(thread_t *thread);

/**
 * @brief Initialize a mutex.
 *
 * @param mutex Pointer to mutex structure.
 * @return 0 on success, non-zero on failure.
 */
int mutex_init(mutex_t *mutex);

/**
 * @brief Lock a mutex.
 *
 * @param mutex Pointer to mutex structure.
 * @return 0 on success, non-zero on failure.
 */
int mutex_lock(mutex_t *mutex);

/**
 * @brief Unlock a mutex.
 *
 * @param mutex Pointer to mutex structure.
 * @return 0 on success, non-zero on failure.
 */
int mutex_unlock(mutex_t *mutex);

/**
 * @brief Destroy a mutex.
 *
 * @param mutex Pointer to mutex structure.
 * @return 0 on success, non-zero on failure.
 */
int mutex_destroy(mutex_t *mutex);

/**
 * @brief Initialize a condition variable.
 *
 * @param cond Pointer to condition variable structure.
 * @return 0 on success, non-zero on failure.
 */
int cond_var_init(cond_var_t *cond);

/**
 * @brief Wait on a condition variable.
 *
 * @param cond Pointer to condition variable structure.
 * @param mutex Pointer to mutex structure.
 * @return 0 on success, non-zero on failure.
 */
int cond_var_wait(cond_var_t *cond, mutex_t *mutex);

/**
 * @brief Signal a condition variable (wake one waiting thread).
 *
 * @param cond Pointer to condition variable structure.
 * @return 0 on success, non-zero on failure.
 */
int cond_var_signal(cond_var_t *cond);

/**
 * @brief Broadcast a condition variable (wake all waiting threads).
 *
 * @param cond Pointer to condition variable structure.
 * @return 0 on success, non-zero on failure.
 */
int cond_var_broadcast(cond_var_t *cond);

/**
 * @brief Destroy a condition variable.
 *
 * @param cond Pointer to condition variable structure.
 * @return 0 on success, non-zero on failure.
 */
int cond_var_destroy(cond_var_t *cond);

#endif // THREAD_H
