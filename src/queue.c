//
// Created by Alan Ćwiek on 8/20/22.
//

#include <stddef.h>
#include <malloc.h>
#include "queue.h"

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

u8 queue_is_full(struct Queue queue) {
    return 0;
}

u8 queue_is_empty(struct Queue queue) {
    return 0;
}

void queue_enqueue(struct Queue *queue, void *data) {

}

void *queue_dequeue(struct Queue *queue) {
    return NULL;
}

