//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_THREAD_H
#define CPU_USAGE_TRACKER_THREAD_H

#include "../common.h"
#include <bits/types/sig_atomic_t.h>

struct thread;
struct Thread *thread_create(void *(*start)(void * arg));
void thread_run(struct Thread *thread, void *arg);
void thread_join(struct Thread *thread);
sig_atomic_t thread_is_running(struct Thread *thread);
void thread_stop(struct Thread *thread);

#endif //CPU_USAGE_TRACKER_THREAD_H
