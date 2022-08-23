//
// Created by Alan Ćwiek on 8/20/22.
//

#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "thread.h"
#include "buffer.h"
#include "thread_manager.h"

static void *thread_routine(void *arg) {
    struct Thread *thread = (struct Thread *) arg;
    return thread->start_routine(arg);
}

struct Thread *
thread_create(char *name, void *(*start)(struct Thread *), struct Buffer *read_buffer,
              struct Buffer *write_buffer, u8 tracked, void *arg) {
    struct Thread *thread = malloc(sizeof(struct Thread));
    u8 result;
    s32 initial_id;
    initial_id = thread_manager_get_next_id();
    thread->thread_id = (pthread_t) initial_id;
    thread->name = name;
    thread->timer = 0;
    thread->start_routine = start;
    thread->read_buffer = read_buffer;
    thread->write_buffer = write_buffer;
    pthread_mutex_init(&thread->mutex, NULL);
    thread->running = TRUE;
    result = (u8) pthread_create(&(thread->thread_id), NULL, thread_routine, thread);
    if (result != 0) {
        perror("Could not create a Thread!");
        exit(1);
    }

    if (tracked) thread_manager_add_thread(thread, initial_id);
    return thread;
}

void thread_join(struct Thread *thread) {
    pthread_join(thread->thread_id, NULL);
}

void thread_stop(struct Thread *thread) {
    thread->running = FALSE;
    if (thread->read_buffer != NULL) buffer_end(thread->read_buffer);
    if (thread->write_buffer != NULL) buffer_end(thread->write_buffer);
    thread_join(thread);
    pthread_mutex_destroy(&thread->mutex);
    free(thread);
}

sig_atomic_t thread_is_running(struct Thread *thread) {
    return thread->running;
}

u8 thread_time(struct Thread *thread, u8 reset) {
    pthread_mutex_lock(&thread->mutex);
    if (reset) {
        thread->timer = 0;
    } else {
        thread->timer++;
    }
    pthread_mutex_unlock(&thread->mutex);
    return thread->timer;
}

void thread_write_to_buffer(struct Thread *thread, void *data) {
    if (thread->write_buffer != NULL) buffer_push(thread->write_buffer, data);
}

void *thread_read_from_buffer(struct Thread *thread) {
    if (thread->read_buffer != NULL) return buffer_pop(thread->read_buffer);
    else return NULL;
}
