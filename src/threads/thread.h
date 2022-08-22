//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_THREAD_H
#define CPU_USAGE_TRACKER_THREAD_H

#include "../common.h"
#include "pthread.h"
#include <signal.h>

struct Thread {
    pthread_t thread_id;
    volatile sig_atomic_t running;
    u8 timer;
    struct Buffer *read_buffer;
    struct Buffer *write_buffer;
    void *(*start_routine)(struct Thread *thread);
};

struct Thread *thread_create(void *(*start)(struct Thread *), struct Buffer *read_buffer, struct Buffer *write_buffer);
void thread_run(struct Thread *thread, void *arg);
void thread_time(struct Thread *thread, u8 reset);
u8 thread_get_timer(struct Thread *thread);
void thread_write_to_buffer(struct Thread *thread, void* data);
void *thread_read_from_buffer(struct Thread *thread);
void thread_join(struct Thread *thread);
sig_atomic_t thread_is_running(struct Thread *thread);
void thread_stop(struct Thread *thread);

#endif //CPU_USAGE_TRACKER_THREAD_H
