//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_QUEUE_H
#define CPU_USAGE_TRACKER_QUEUE_H

#include "../common.h"

#define QUEUE_NEW(type, capacity) queue_create(capacity, sizeof(type))

/* Queue holding up to 255 elements*/
struct Queue;
struct Queue *queue_create(u8 capacity, size_t size);
u8 queue_is_full(struct Queue* queue);
u8 queue_is_empty(struct Queue* queue);
void queue_enqueue(struct Queue* queue, void* data);
void* queue_dequeue(struct Queue* queue);
void queue_destroy(struct Queue* queue);

#endif //CPU_USAGE_TRACKER_QUEUE_H
