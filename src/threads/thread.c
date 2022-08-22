//
// Created by Alan Ćwiek on 8/20/22.
//

#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include "thread.h"

struct Thread *thread_create(void *(*start)(struct Thread *), struct Buffer *buffer) {
    pthread_t thread_id;
    struct Thread *thread = malloc(sizeof(struct Thread));
    thread->start_routine = start;
    thread->thread_id = thread_id;
    thread->buffer = buffer;
    return thread;
}

static void *thread_routine(void *arg) {
    struct Thread *thread = (struct Thread *) arg;
    thread->start_routine(arg);
}

void thread_run(struct Thread *thread, void *arg) {
    thread->running = TRUE;
    u8 result = pthread_create(&(thread->thread_id), NULL, thread_routine, thread);
    if (result != 0) {
        perror("Could not create a Thread!");
        exit(1);
    }
}

void thread_join(struct Thread *thread) {
    pthread_join(thread->thread_id, NULL);
}

void thread_stop(struct Thread *thread) {
    thread->running = FALSE;
}

sig_atomic_t thread_is_running(struct Thread *thread) {
    return thread->running;
}

u8 thread_get_timer(struct Thread *thread) {
    return thread->timer;
}

void thread_time(struct Thread *thread, u8 reset) {
    if (reset) {
        thread->timer = 0;
    } else {
        thread->timer++;
    }
}
