//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_QUEUE_H
#define CPU_USAGE_TRACKER_QUEUE_H

#include "../common.h"

#define QUEUE_NEW(type, capacity) queue_create(capacity, sizeof(type))

/* Queue holding up to 255 elements*/
typedef struct Queue Queue;

Queue *queue_create(u8 capacity, size_t size);

u8 queue_is_full(Queue *queue);

u8 queue_is_empty(Queue *queue);

void queue_enqueue(Queue *queue, void *data);

void *queue_dequeue(Queue *queue);

void queue_destroy(Queue *queue);

#endif //CPU_USAGE_TRACKER_QUEUE_H
