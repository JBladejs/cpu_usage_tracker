//
// Created by Alan Ćwiek on 8/20/22.
//

#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include "thread.h"
#include "buffer.h"

struct Thread *thread_create(char *name, void *(*start)(struct Thread *), struct Buffer *read_buffer, struct Buffer *write_buffer) {
    pthread_t thread_id;
    struct Thread *thread = malloc(sizeof(struct Thread));
    thread->name = name;
    thread->start_routine = start;
    thread->thread_id = thread_id;
    thread->read_buffer = read_buffer;
    thread->write_buffer = write_buffer;
    return thread;
}

static void *thread_routine(void *arg) {
    struct Thread *thread = (struct Thread *) arg;
    return thread->start_routine(arg);
}

void thread_run(struct Thread *thread) {
    u8 result;
    thread->running = TRUE;
    result = (u8) pthread_create(&(thread->thread_id), NULL, thread_routine, thread);
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

void thread_write_to_buffer(struct Thread *thread, void *data) {
    if (thread->write_buffer != NULL) buffer_push(thread->write_buffer, data);
}

void *thread_read_from_buffer(struct Thread *thread) {
    if (thread->read_buffer != NULL)return buffer_pop(thread->read_buffer);
    else return NULL;
}
