//
// Created by Alan Ćwiek on 8/20/22.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

Queue *queue_create(u8 capacity, size_t size) {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->element_size = size;
    queue->front = queue->size = 0;
    queue->back = capacity - 1;
    queue->data = malloc(capacity * size);
    return queue;
}

u8 queue_is_full(Queue *queue) {
    return queue->size == queue->capacity;
}

u8 queue_is_empty(Queue *queue) {
    return queue->size == 0;
}

void queue_enqueue(Queue *queue, void *data) {
    if (queue_is_full(queue)) {
        return;
    }
    queue->back = (queue->back + 1) % queue->capacity;
    queue->size++;
    memcpy((s8 *) queue->data + queue->back * queue->element_size, data, queue->element_size);
}

void *queue_dequeue(Queue *queue) {
    void *data;
    if (queue_is_empty(queue)) {
        return NULL;
    }
    data = malloc(queue->element_size);
    memcpy(data, (s8 *) queue->data + queue->front * queue->element_size, queue->element_size);
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}

void queue_destroy(Queue *queue) {
    free(queue->data);
    free(queue);
}

