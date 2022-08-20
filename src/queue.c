//
// Created by Alan Ćwiek on 8/20/22.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "analyzer.h"


struct Queue {
    u8 front, back, size;
    u8 capacity;
    size_t element_size;
    void* data;
};

struct Queue *queue_create(u8 capacity, size_t size){
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->element_size = size;
    queue->front = queue->size = 0;
    queue->back = capacity - 1;
    queue->data = malloc(capacity * size);
}

u8 queue_is_full(struct Queue* queue) {
    return queue->size == queue->capacity;
}

u8 queue_is_empty(struct Queue* queue) {
    return queue->size == 0;
}

void queue_enqueue(struct Queue *queue, void* data) {
    if (queue_is_full(queue)) {
        return;
    }
    queue->back = (queue->back + 1) % queue->capacity;
    queue->size++;
    memcpy(queue->data + queue->back * queue->element_size, data, queue->element_size);
}

void *queue_dequeue(struct Queue *queue) {
    if (queue_is_empty(queue)) {
        return NULL;
    }
    void* data = malloc(queue->element_size);
    memcpy(data, queue->data + queue->front * queue->element_size, queue->element_size);
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}

void queue_destroy(struct Queue *queue) {
    free(queue->data);
    free(queue);
}

