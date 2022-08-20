//
// Created by Alan Ćwiek on 8/20/22.
//

#include <stddef.h>
#include "queue.h"

struct Queue {
    u8 front, back, size;
    u8 capacity;
    size_t element_size;
    void* data;
};

struct Queue create_queue(u8 capacity) {
    struct Queue result;
    return result;
}

u8 is_queue_full(struct Queue queue) {
    return 0;
}

u8 is_queue_empty(struct Queue queue) {
    return 0;
}

void enqueue(struct Queue *queue, void *data) {

}

void *dequeue(struct Queue *queue) {
    return NULL;
}

