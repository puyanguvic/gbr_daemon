#include "thread.h"
#include <stdlib.h>

/**
 * @brief Create a new thread.
 */
int thread_create(thread_t *thread, thread_func_t func, void *arg)
{
    if (!thread || !func)
    {
        return -1;
    }
    return pthread_create(&thread->thread_id, NULL, func, arg);
}

/**
 * @brief Join a thread.
 */
int thread_join(thread_t *thread)
{
    if (!thread)
    {
        return -1;
    }
    return pthread_join(thread->thread_id, NULL);
}

/**
 * @brief Initialize a mutex.
 */
int mutex_init(mutex_t *mutex)
{
    if (!mutex)
    {
        return -1;
    }
    return pthread_mutex_init(&mutex->mutex, NULL);
}

/**
 * @brief Lock a mutex.
 */
int mutex_lock(mutex_t *mutex)
{
    if (!mutex)
    {
        return -1;
    }
    return pthread_mutex_lock(&mutex->mutex);
}

/**
 * @brief Unlock a mutex.
 */
int mutex_unlock(mutex_t *mutex)
{
    if (!mutex)
    {
        return -1;
    }
    return pthread_mutex_unlock(&mutex->mutex);
}

/**
 * @brief Destroy a mutex.
 */
int mutex_destroy(mutex_t *mutex)
{
    if (!mutex)
    {
        return -1;
    }
    return pthread_mutex_destroy(&mutex->mutex);
}

/**
 * @brief Initialize a condition variable.
 */
int cond_var_init(cond_var_t *cond)
{
    if (!cond)
    {
        return -1;
    }
    return pthread_cond_init(&cond->cond, NULL);
}

/**
 * @brief Wait on a condition variable.
 */
int cond_var_wait(cond_var_t *cond, mutex_t *mutex)
{
    if (!cond || !mutex)
    {
        return -1;
    }
    return pthread_cond_wait(&cond->cond, &mutex->mutex);
}

/**
 * @brief Signal a condition variable.
 */
int cond_var_signal(cond_var_t *cond)
{
    if (!cond)
    {
        return -1;
    }
    return pthread_cond_signal(&cond->cond);
}

/**
 * @brief Broadcast a condition variable.
 */
int cond_var_broadcast(cond_var_t *cond)
{
    if (!cond)
    {
        return -1;
    }
    return pthread_cond_broadcast(&cond->cond);
}

/**
 * @brief Destroy a condition variable.
 */
int cond_var_destroy(cond_var_t *cond)
{
    if (!cond)
    {
        return -1;
    }
    return pthread_cond_destroy(&cond->cond);
}
