//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_THREAD_H
#define CPU_USAGE_TRACKER_THREAD_H

struct thread;
struct Thread *thread_create(void *(*start)(void * arg), void (*destroy)());
void thread_run(struct Thread *thread, void *arg);
void thread_join(struct Thread *thread);

#endif //CPU_USAGE_TRACKER_THREAD_H
