//
// Created by Alan Ćwiek on 8/20/22.
//

#ifndef CPU_USAGE_TRACKER_STATS_H
#define CPU_USAGE_TRACKER_STATS_H

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

struct Stats;
struct Stats *stats_initialize(char *file_name);
u16 stats_get_core_count(struct Stats *reader);
void stats_read(struct Stats *reader, struct CpuStats *stat);
void stat_destroy(struct Stats *reader);

#endif //CPU_USAGE_TRACKER_STATS_H
