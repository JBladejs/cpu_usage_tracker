//
// Created by Alan Ćwiek on 8/18/22.
//

#ifndef CPU_USAGE_TRACKER_READER_H
#define CPU_USAGE_TRACKER_READER_H

#include "common.h"

struct CpuStats {
    u64 user;
    u64 nice;
    u64 system;
    u64 idle;
    u64 iowait;
    u64 irq;
    u64 softirq;
    u64 steal;
};

void *reader_init(void *arg);
void reader_destroy();

#endif //CPU_USAGE_TRACKER_READER_H
