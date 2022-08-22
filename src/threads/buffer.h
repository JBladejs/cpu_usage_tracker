//
// Created by Alan Ćwiek on 8/22/22.
//

#ifndef CPU_USAGE_TRACKER_BUFFER_H
#define CPU_USAGE_TRACKER_BUFFER_H

#include <semaphore.h>
#include "../common.h"

#define BUFFER_NEW(type, capacity) buffer_create(capacity, sizeof(type))
#define BUFFER_ARRAY_NEW(type, amount, capacity) buffer_create(capacity, sizeof(type) * amount)

struct Buffer {
    struct Queue *queue;
    pthread_mutex_t mutex;
    sem_t empty, full;
};

struct Buffer *buffer_create(u8 capacity, size_t element_size);
void buffer_push(struct Buffer *buffer, void *data);
void *buffer_pop(struct Buffer *buffer);
void buffer_destroy(struct Buffer *buffer);

#endif //CPU_USAGE_TRACKER_BUFFER_H
