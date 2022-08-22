//
// Created by Alan Ćwiek on 8/21/22.
//

#ifndef CPU_USAGE_TRACKER_WATCHDOG_H
#define CPU_USAGE_TRACKER_WATCHDOG_H
#include "thread.h"

void watchdog_init(struct Thread **threads, size_t thread_count);
struct Thread *watchdog_get_thread(void);

#endif //CPU_USAGE_TRACKER_WATCHDOG_H
