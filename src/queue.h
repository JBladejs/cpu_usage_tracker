//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_QUEUE_H
#define CPU_USAGE_TRACKER_QUEUE_H

#include "common.h"

/* Queue holding up to 255 elements*/
struct Queue;
struct Queue create_queue(u8 capacity);
u8 is_queue_full(struct Queue queue);
u8 is_queue_empty(struct Queue queue);
void enqueue(struct Queue* queue, void* data);
void* dequeue(struct Queue* queue);

#endif //CPU_USAGE_TRACKER_QUEUE_H
