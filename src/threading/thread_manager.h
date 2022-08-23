//
// Created by Alan Ćwiek on 8/23/22.
//

#ifndef CPU_USAGE_TRACKER_THREAD_MANAGER_H
#define CPU_USAGE_TRACKER_THREAD_MANAGER_H

#include <bits/pthreadtypes.h>
#include "../common.h"

struct ThreadManager {
    struct Thread *threads[10];
    pthread_t watchdog_thread;
    s32 index;
    u32 active_threads;
};

struct ThreadManager *thread_manager_instance(void);
s32 thread_manager_get_next_id(void);
void thread_manager_add_thread(struct Thread *thread, s32 id);
void thread_manager_join(void);
void thread_manager_destroy_all(void);

#endif //CPU_USAGE_TRACKER_THREAD_MANAGER_H
