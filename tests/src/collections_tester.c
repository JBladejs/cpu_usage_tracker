//
// Created by Alan Ćwiek on 8/22/22.
//

#include <stddef.h>
#include <assert.h>
#include "../../src/collections/queue.h"

static void queue_test(void) {
    int data[6];
    Queue *queue = QUEUE_NEW(int, 5);
    assert(queue != NULL);
    assert(queue_is_empty(queue));
    assert(!queue_is_full(queue));

    for (int i = 0; i < 6; ++i) {
        data[i] = i + 1;
    }

    queue_enqueue(queue, &data[0]);
    assert(!queue_is_empty(queue));
    assert(!queue_is_full(queue));
    assert(*(int *) queue_dequeue(queue) == 1);
    assert(queue_is_empty(queue));

    queue_enqueue(queue, &data[1]);
    queue_enqueue(queue, &data[2]);
    queue_enqueue(queue, &data[3]);
    queue_enqueue(queue, &data[4]);
    queue_enqueue(queue, &data[5]);

    assert(!queue_is_empty(queue));
    assert(queue_is_full(queue));
    assert(*(int *) queue_dequeue(queue) == 2);
    assert(!queue_is_full(queue));
    assert(!queue_is_empty(queue));
    assert(*(int *) queue_dequeue(queue) == 3);
    assert(*(int *) queue_dequeue(queue) == 4);
    assert(*(int *) queue_dequeue(queue) == 5);
    assert(*(int *) queue_dequeue(queue) == 6);
    assert(queue_is_empty(queue));

    queue_destroy(queue);
}

int main(void) {
    queue_test();
    return 0;
}
