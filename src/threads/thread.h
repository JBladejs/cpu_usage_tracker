//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_THREAD_H
#define CPU_USAGE_TRACKER_THREAD_H

#include "../common.h"
#include "pthread.h"
#include <bits/types/sig_atomic_t.h>

struct Thread {
    pthread_t thread_id;
    volatile sig_atomic_t running;
    u8 timer;
    void *(*start_routine)(struct Thread *thread);
};

struct Thread *thread_create(void *(*start)(struct Thread *thread));
void thread_run(struct Thread *thread, void *arg);
void thread_time(struct Thread *thread, u8 reset);
u8 thread_get_timer(struct Thread *thread);
void thread_join(struct Thread *thread);
sig_atomic_t thread_is_running(struct Thread *thread);
void thread_stop(struct Thread *thread);

#endif //CPU_USAGE_TRACKER_THREAD_H
