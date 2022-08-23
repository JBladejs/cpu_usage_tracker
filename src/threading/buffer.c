//
// Created by Alan Ćwiek on 8/22/22.
//

#include <malloc.h>
#include <pthread.h>
#include "buffer.h"
#include "../collections/queue.h"

Buffer *buffer_create(u8 capacity, size_t element_size) {
    Buffer *buffer = (Buffer *) malloc(sizeof(Buffer));
    buffer->queue = queue_create(capacity, element_size);
    pthread_mutex_init(&buffer->mutex, NULL);
    sem_init(&buffer->empty, 0, capacity);
    sem_init(&buffer->full, 0, 0);
    buffer->active = TRUE;
    return buffer;
}

void buffer_push(Buffer *buffer, void *data) {
    sem_wait(&buffer->empty);
    pthread_mutex_lock(&buffer->mutex);
//    if (!buffer->active) return;

    queue_enqueue(buffer->queue, data);

    pthread_mutex_unlock(&buffer->mutex);
    sem_post(&buffer->full);
}

void *buffer_pop(Buffer *buffer) {
    void *data;
    sem_wait(&buffer->full);
    pthread_mutex_lock(&buffer->mutex);
//    if (!buffer->active) return NULL;

    data = queue_dequeue(buffer->queue);

    pthread_mutex_unlock(&buffer->mutex);
    sem_post(&buffer->empty);

    return data;
}

void buffer_end(Buffer *buffer) {
    buffer->active = FALSE;
    sem_post(&buffer->empty);
    sem_post(&buffer->full);
}

void buffer_destroy(Buffer *buffer) {
    queue_destroy(buffer->queue);
    pthread_mutex_destroy(&buffer->mutex);
    sem_destroy(&buffer->empty);
    sem_destroy(&buffer->full);
    free(buffer);
}
