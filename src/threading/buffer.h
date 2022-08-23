//
// Created by Alan Ćwiek on 8/22/22.
//

#ifndef CPU_USAGE_TRACKER_BUFFER_H
#define CPU_USAGE_TRACKER_BUFFER_H

#include <semaphore.h>
#include "../common.h"

#define BUFFER_NEW(type, capacity) buffer_create(capacity, sizeof(type))
#define BUFFER_ARRAY_NEW(type, amount, capacity) buffer_create(capacity, sizeof(type) * amount)

typedef struct Buffer {
    struct Queue *queue;
    pthread_mutex_t mutex;
    sem_t empty, full;
    u8 active;

    //padding
    u64 : 56;
} Buffer;

Buffer *buffer_create(u8 capacity, size_t element_size);

void buffer_push(Buffer *buffer, void *data);

void *buffer_pop(Buffer *buffer);

void buffer_end(Buffer *buffer);

void buffer_destroy(Buffer *buffer);

#endif //CPU_USAGE_TRACKER_BUFFER_H
