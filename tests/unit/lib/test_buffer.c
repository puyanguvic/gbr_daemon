#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

int main(void)
{
    printf("Running test_buffer...\n");

    buffer_t *buf = buffer_create(0);
    if (!buf)
    {
        printf("Failed to create buffer.\n");
        return 1;
    }

    const char *test_data = "Hello, Buffer!";
    if (buffer_append(buf, test_data, strlen(test_data)) != 0)
    {
        printf("Failed to append data to buffer.\n");
        buffer_free(buf);
        return 1;
    }

    if (buf->size != strlen(test_data))
    {
        printf("Buffer size mismatch.\n");
        buffer_free(buf);
        return 1;
    }

    char read_data[20] = {0};
    if (buffer_read(buf, read_data, strlen(test_data)) != 0)
    {
        printf("Failed to read data from buffer.\n");
        buffer_free(buf);
        return 1;
    }

    if (strcmp(test_data, read_data) != 0)
    {
        printf("Data mismatch: expected '%s', got '%s'\n", test_data, read_data);
        buffer_free(buf);
        return 1;
    }

    if (buffer_remaining(buf) != 0)
    {
        printf("Buffer remaining data mismatch.\n");
        buffer_free(buf);
        return 1;
    }

    buffer_reset(buf);
    if (buf->size != 0 || buf->position != 0)
    {
        printf("Buffer reset failed.\n");
        buffer_free(buf);
        return 1;
    }

    buffer_free(buf);
    printf("All buffer tests passed.\n");
    return 0;
}
