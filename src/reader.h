//
// Created by Alan Ćwiek on 8/18/22.
//

#ifndef CPU_USAGE_TRACKER_READER_H
#define CPU_USAGE_TRACKER_READER_H

#include "common.h"

typedef struct CpuStats {
    u64 user;
    u64 nice;
    u64 system;
    u64 idle;
    u64 iowait;
    u64 irq;
    u64 softirq;
    u64 steal;
} CpuStats;

void *reader_init(void *arg);
void reader_destroy();
//u8 reader_load_file();
//u8 reader_close_file();

#endif //CPU_USAGE_TRACKER_READER_H
