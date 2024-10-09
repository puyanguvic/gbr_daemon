#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

#define NUM_ITEMS 10

typedef struct
{
    int buffer[NUM_ITEMS];
    int count;
    mutex_t mutex;
    cond_var_t cond;
} shared_data_t;

void *producer(void *arg)
{
    shared_data_t *data = (shared_data_t *)arg;
    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        // Lock mutex before modifying shared data
        mutex_lock(&data->mutex);
        data->buffer[data->count++] = i;
        printf("Producer: produced item %d\n", i);
        // Signal the consumer
        cond_var_signal(&data->cond);
        // Unlock mutex
        mutex_unlock(&data->mutex);
        // Simulate work
        // usleep(100000); // Uncomment to slow down the producer
    }
    return NULL;
}

void *consumer(void *arg)
{
    shared_data_t *data = (shared_data_t *)arg;
    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        // Lock mutex before accessing shared data
        mutex_lock(&data->mutex);
        // Wait for data to be available
        while (data->count == 0)
        {
            cond_var_wait(&data->cond, &data->mutex);
        }
        int item = data->buffer[--data->count];
        printf("Consumer: consumed item %d\n", item);
        // Unlock mutex
        mutex_unlock(&data->mutex);
        // Process item
        // usleep(150000); // Uncomment to simulate processing time
    }
    return NULL;
}

int main(void)
{
    printf("Running thread management tests...\n");

    shared_data_t data;
    data.count = 0;
    mutex_init(&data.mutex);
    cond_var_init(&data.cond);

    thread_t prod_thread, cons_thread;

    // Create producer and consumer threads
    if (thread_create(&prod_thread, producer, &data) != 0)
    {
        printf("Failed to create producer thread.\n");
        return 1;
    }

    if (thread_create(&cons_thread, consumer, &data) != 0)
    {
        printf("Failed to create consumer thread.\n");
        return 1;
    }

    // Wait for threads to finish
    thread_join(&prod_thread);
    thread_join(&cons_thread);

    // Clean up
    mutex_destroy(&data.mutex);
    cond_var_destroy(&data.cond);

    printf("All thread management tests passed.\n");
    return 0;
}
